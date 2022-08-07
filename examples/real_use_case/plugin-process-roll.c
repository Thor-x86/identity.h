#include <stdlib.h>
#include <stdio.h>

#include <identity.h>
#include "plugin-protocol.h"

// You set the role by string, the compiler automatically hash it to integer
int role = IDENTITY_INT("process");

plugin_message_t node(plugin_message_t input)
{
	// We have to re-initialize variable at heap memory because input will be
	// freed after this node
	size_t message_size = CALCULATE_MESSAGE_SIZE(input->size);
	plugin_message_t output = malloc(message_size);

	// For this node, input and output size are equal
	output->size = input->size;

	// Roll string to left, except for NUL character
	for (int i = 0; i < output->size - 2; i++)
	{
		output->data[i] = input->data[i + 1];
	};

	// Move leftmost character to right
	output->data[output->size - 2] = input->data[0];

	// Put NUL character to mark the end of string
	output->data[output->size - 1] = '\0';

	return output;
}