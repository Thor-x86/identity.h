#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Requires fopen and fclose to read a file
#include <fcntl.h>

// Requires errno to get standard error code after failed to open the file
#include <errno.h>

// Requires strerror to translate standard error code as human readable message
#include <error.h>

// Requires stat to get file size
#include <sys/stat.h>

#include <identity.h>
#include "plugin-protocol.h"

// You set the role by string, the compiler automatically hash it to integer
int role = IDENTITY_INT("input");

plugin_message_t node(plugin_message_t input)
{
	// Initialize file path string in stack memory
	char file_path[256];

	// Ask user to input the file path
	fputs("Input a file path: ", stdout);

	// Wait and get input from user
	fgets(file_path, sizeof file_path, stdin);

	// Find the file path string length then replace newline to NUL
	size_t file_path_length = strlen(file_path);
	file_path[file_path_length - 1] = '\0';

	// Prepare empty message in case of failure
	plugin_message_t empty = NULL;

	// Open the requested file. If not exist, report to user then
	// pass an empty message to the next node
	FILE *file = fopen(file_path, "rb");
	if (!file)
	{
		fprintf(
			stderr,
			"Cannot open \"%s\" because %s\n",
			file_path,
			strerror(errno));
		goto on_fail;
	}

	// Get the file size
	size_t file_size;
	{
		struct stat file_info;
		stat(file_path, &file_info);
		file_size = file_info.st_size;
	}

	// Warn user if it's empty
	if (!file_size)
	{
		fprintf(
			stderr,
			"File \"%s\" is either empty or not a real file, try another.\n",
			file_path);
		goto on_fail;
	}

	// Output data is added one for NUL character
	size_t data_size = file_size + 1;

	// Initialize shared variable at heap memory
	size_t message_size = CALCULATE_MESSAGE_SIZE(data_size);
	plugin_message_t output = malloc(message_size);

	// Remember, message size is limited to 255 characters including NUL.
	// For simplicity sake, exceeding data will be truncated
	if (data_size > 255)
		output->size = 255;
	else
		output->size = data_size;

	// Load the file to RAM
	fread(output->data, sizeof(char), file_size, file);

	// Don't forget to close the file after use
	fclose(file);

	// Make sure the data ended with NUL
	output->data[output->size - 1] = '\0';

	return output;

on_fail:
	// Fallback to empty message if failed to load the file
	empty = malloc(CALCULATE_MESSAGE_SIZE(1));
	empty->size = 1;
	empty->data[0] = '\0';
	return empty;
}