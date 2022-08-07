#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <identity.h>
#include "plugin-protocol.h"

// You set the role by string, the compiler automatically hash it to integer
int role = IDENTITY_INT("input");

plugin_message_t node(plugin_message_t input)
{
	// Initialize buffer
	char buffer[255];
	memset(buffer, 0, sizeof buffer);

	do
	{
		// Prepend "> " to indicate user can type now
		fputs("> ", stdout);

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