#include <stdlib.h>
#include <stdio.h>

#include <identity.h>
#include "plugin-protocol.h"

// This equals 32, ASCII code substraction between lowercase and uppercase.
// Remember: lowercase > uppercase in ASCII code
#define LETTER_CASE_DELTA ('a' - 'A')

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

	// Toggle letter case, character by character
	for (int i = 0; i < output->size; i++)
	{
		// Stop the operation if NUL character found,
		// as it known as end of string
		if (input->data[i] == '\0')
		{
			output->data[i] = '\0';
			break;
		}

		// Convert lowercase to uppercase
		else if (input->data[i] >= 'a' && input->data[i] <= 'z')
			output->data[i] = input->data[i] - LETTER_CASE_DELTA;

		// Convert uppercase to lowercase
		else if (input->data[i] >= 'A' && input->data[i] <= 'Z')
			output->data[i] = input->data[i] + LETTER_CASE_DELTA;

		// Not an alphabetical letter, assign it as-is
		else
			output->data[i] = input->data[i];
	};

	return output;
}