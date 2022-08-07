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

	// Now, let's reverse the input!
	// NOTE: All strings have trailing NUL for a reason, make sure it isn't
	//       being moved to beginning of string, otherwise it prints nothing.
	for (int i = 0; i < output->size - 1; i++)
	{
		output->data[i] = input->data[output->size - i - 2];
	}

	// Output also need trailing NUL
	output->data[output->size - 1] = '\0';

	return output;
}