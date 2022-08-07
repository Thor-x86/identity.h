#include <stdlib.h>
#include <stdio.h>

#include <identity.h>

identity_t id = IDENTITY("Hello, World!");

int main()
{
	printf("Identity of \"Hello, World!\" is %llu\n", id);
	return EXIT_SUCCESS;
}