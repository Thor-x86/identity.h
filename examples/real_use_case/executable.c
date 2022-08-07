#include <stdlib.h>
#include <stdio.h>

// Requires standard error codes (EINVAL, ENOKEY, ENOENT, ...)
// see https://man7.org/linux/man-pages/man3/errno.3.html
#include <errno.h>

// Requires signal function for doing something on exit request by user
#include <signal.h>

// Requires dlopen, dlsym, and dlclose for load/unload plugins
#include <dlfcn.h>

// Requires IDENTITY_INT
#include <identity.h>

// Requires plugin_message_t
#include "plugin-protocol.h"

// This identifies each plugin's role.
enum role_e
{
	ROLE_INPUT = IDENTITY_INT("input"),
	ROLE_PROCESS = IDENTITY_INT("process"),
	ROLE_OUTPUT = IDENTITY_INT("output"),
};

// Keep in mind that IDENTITY(...) only accepts literal string.
// So we have to declare the string independently.
const char role_input_str[] = "input";
const char role_process_str[] = "process";
const char role_output_str[] = "output";

// This just a syntactic sugar to "void*" type for library handle
typedef void *plugin_handle_t;

// These are plugin handles, their job is to point memory address where the
// plugin located in RAM. We have to make these global variable because they
// need to be cleaned-up before the executable exit.
plugin_handle_t input = NULL;
plugin_handle_t process = NULL;
plugin_handle_t output = NULL;

// This also being cleaned up before exit.
plugin_message_t last_output_result = NULL;

// These are function headers. The purpose is to tell the compiler these
// functions are exist somewhere below the source code.
void cleanup();
void on_interruption();

// Define plugin_node_t type as a pointer to function
typedef plugin_message_t (*plugin_node_t)(const plugin_message_t input);

int main(int argument_count, char **arguments)
{
	// Check for executable parameters (a.k.a. arguments)
	if (argument_count < 2)
	{
		// Tell user what's wrong via standard error stream
		fputs("Please input path of plugins, separated with space\n", stderr);

		// arguments[0] is executable name. In a few cases, it can be NULL
		const char *executable_name = NULL;
		if (argument_count)
			executable_name = arguments[0];
		else
			executable_name = "real_use_case";

		// Print usage clue via standard output stream
		printf(
			"\n"
			"USAGE:\n"
			"    %s <input plugin> <process plugin> <output plugin>\n",
			executable_name);

		// Also tell an example
		printf(
			"\n"
			"EXAMPLE:\n"
#if defined(__APPLE__) || defined(__MACH__) // MacOS uses .dylib instead of .so
			"    %s ./input-terminal.dylib ./process-toggle_case.dylib ./output-terminal.dylib\n"
#else
			"    %s ./input-terminal.so ./process-toggle_case.so ./output-terminal.so\n"
#endif
			"\n",
			executable_name);

		// Use correct error codes from errno.h,
		// this is useful for automation
		return EINVAL;
	}

	// Let cleanup function to be called right before exit
	atexit(&cleanup);

	// Also assign on_interruption function as signal handler to fix the
	// error code to success
	puts("Press CTRL+C to stop\n");
	signal(SIGINT, &on_interruption);
	signal(SIGTERM, &on_interruption);
	signal(SIGHUP, &on_interruption);

	// Load the requested plugins
	for (int i = 1; i < argument_count; i++)
	{
		plugin_handle_t plugin = dlopen(arguments[i], RTLD_NOW);
		if (!plugin)
		{
			fprintf(
				stderr,
				"Failed to load \"%s\" plugin because %s.\n",
				arguments[i],
				dlerror() ?: "of unknown cause");
			return errno ?: EXIT_FAILURE;
		}

		// Get the role key
		enum role_e *role = dlsym(plugin, "role");
		if (!role)
		{
			fprintf(
				stderr,
				"There is no \"role\" constant in \"%s\".\n",
				arguments[i]);
			return ENOKEY;
		}

		const char duplicate_error[] = "Duplicate %s role.\n";

		// Assign plugin based on its role,
		// this is where identity.h being useful
		switch (*role)
		{
		case ROLE_INPUT:
			if (input)
			{
				printf(duplicate_error, role_input_str);
				return EINVAL;
			}
			input = plugin;
			break;
		case ROLE_PROCESS:
			if (process)
			{
				printf(duplicate_error, role_process_str);
				return EINVAL;
			}
			process = plugin;
			break;
		case ROLE_OUTPUT:
			if (output)
			{
				printf(duplicate_error, role_output_str);
				return EINVAL;
			}
			output = plugin;
			break;
		default:
			fprintf(
				stderr,
				"Plugin \"%s\" has invalid role.\n",
				arguments[i]);
			return EINVAL;
		}
	}

	// Check for plugin completeness
	const char empty_role_error[] = "There is no plugin with %s role.\n";
	if (!input)
		fprintf(stderr, empty_role_error, role_input_str);
	if (!process)
		fprintf(stderr, empty_role_error, role_process_str);
	if (!output)
		fprintf(stderr, empty_role_error, role_output_str);
	if (!input || !process || !output)
		return EINVAL;

	// Get the node function on each plugin
	plugin_node_t input_node = dlsym(input, "node");
	plugin_node_t process_node = dlsym(process, "node");
	plugin_node_t output_node = dlsym(output, "node");

	// Make sure the nodes are not NULL
	const char no_node_error[] = "There is no node function at %s.\n";
	if (!input_node)
		fprintf(stderr, no_node_error, role_input_str);
	if (!process_node)
		fprintf(stderr, no_node_error, role_process_str);
	if (!output_node)
		fprintf(stderr, no_node_error, role_output_str);
	if (!input_node || !process_node || !output_node)
		return ENOKEY;

	while (1)
	{
		plugin_message_t result_of_input = input_node(last_output_result);
		free(last_output_result); // Keep in mind that the result is in Heap

		plugin_message_t result_of_process = process_node(result_of_input);
		free(result_of_input);

		last_output_result = output_node(result_of_process);
		free(result_of_process);

		// No feedback result? exit the program.
		if (!last_output_result)
			break;
	}

	puts("\n[Finished]");
	return EXIT_SUCCESS;
}

// This automatically be called right before exit
void cleanup()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	if (last_output_result)
		free(last_output_result);
	if (input)
		dlclose(input);
	if (process)
		dlclose(process);
	if (output)
		dlclose(output);
}

// We don't call this explicitly, it will be called automatically if the user
// hits CTRL+C on terminal or closes the terminal window.
void on_interruption(int signal_code)
{
	puts("\n[Stopped]");
	exit(EXIT_SUCCESS);
}