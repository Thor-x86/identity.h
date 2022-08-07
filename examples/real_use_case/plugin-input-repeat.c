#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <identity.h>
#include "plugin-protocol.h"

// You set the role by string, the compiler automatically hash it to integer
int role = IDENTITY_INT("input");

#if _POSIX_C_SOURCE >= 199309L
// Requires nanosleep to do a delay
#include <time.h>

// This declares how long the delay needed
const struct timespec delay = {
	.tv_sec = 0,
	.tv_nsec = 100000000L // 100 milliseconds
};
#else
// Fallback to older delay API if compiler not support it
#include <unistd.h>
#endif

plugin_message_t node(plugin_message_t input)
{
	// input == NULL means the executable just started
	if (!input)
	{
		// Initialize buffer
		char buffer[255];
		memset(buffer, 0, sizeof buffer);

		do
		{
			// Ask user to input what to repeat
			fputs("Input a text: ", stdout);

			// Wait and get input from user
			fgets(buffer, sizeof buffer, stdin);
		} while (!buffer[0] || buffer[0] == '\n'); // Make sure it's not empty

		// Count how many characters from user
		size_t user_input_length = strlen(buffer);

		// Add trailing NUL character
		buffer[user_input_length - 1] = '\0';

		// Calculate overall message size
		unsigned char message_size = CALCULATE_MESSAGE_SIZE(user_input_length);

		// Initialize shared variable at heap memory
		plugin_message_t output = malloc(message_size);

		// Inform to the next node how big the data is,
		output->size = user_input_length;

		// Copy buffer into the message that will be passed to the next node
		memcpy(output->data, buffer, user_input_length);

		// We can now pass the result to process node
		return output;
	}

	// input is not null, that means user already inputted something
	else
	{
#if _POSIX_C_SOURCE >= 199309L
		// Give a delay to make the text readable
		nanosleep(&delay, NULL);
#else
		// Delay 1 second instead, if nanosleep isn't supported by compiler
		sleep(1);
#endif

		// Remove previous line
		fputs("\033[1A", stdout);

		// Clone input because it will be freed after this node
		size_t message_size = CALCULATE_MESSAGE_SIZE(input->size);
		plugin_message_t output = malloc(message_size);
		memcpy(output, input, message_size);
		return output;
	}
}