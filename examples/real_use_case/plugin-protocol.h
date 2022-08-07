// Header guard, this prevents false error
// on some complex dependency ecosystem
#ifndef PLUGIN_PROTOCOL_DEFINED
#define PLUGIN_PROTOCOL_DEFINED

// Structurize how all plugins exchange data
struct plugin_message
{
	// Maximum size = size of char (255)
	unsigned char size;

	// Compiler won't know this size,
	// because the size is dynamically set with malloc
	char data[];
};

// Shorthand for pointer of struct plugin_message
typedef struct plugin_message *plugin_message_t;

// Macro for calculating overall plugin_message size
#define CALCULATE_MESSAGE_SIZE(DATA_SIZE) \
	(sizeof(struct plugin_message) + DATA_SIZE)

#endif // #ifndef PLUGIN_PROTOCOL_DEFINED