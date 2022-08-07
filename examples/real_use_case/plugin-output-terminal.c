#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <identity.h>
#include "plugin-protocol.h"

// You set the role by string, the compiler automatically hash it to integer
int role = IDENTITY_INT("output");

plugin_message_t node(plugin_message_t input)
{
	// Print to standard output, with newline at the end
	puts(input->data);

	// We need to initialize shared variable at heap memory for feedback input
	size_t message_size = CALCULATE_MESSAGE_SIZE(input->size);
	plugin_message_t output = malloc(message_size);
	memcpy(output, input, message_size);
	return output;
}