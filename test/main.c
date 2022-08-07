#include <assert.h>
#include <stdio.h>

#include <identity/define.h>
#ifndef IDENTITY
#error The "IDENTITY" macro did not exist when being included with <identity/define.h>
#endif

#include <identity/undefine.h>
#ifdef IDENTITY
#error The "IDENTITY" macro supposed to be undefined after include <identity/undefine.h>
#endif

#include <identity.h>
#ifndef IDENTITY
#error The "IDENTITY" macro did not exist when being included with <identity.h>
#endif

#include <identity/undefine.h>
#ifdef IDENTITY
#error The "IDENTITY" macro supposed to be undefined after include <identity.h> then <identity/undefine.h>
#endif

#include <identity.h>
identity_t example_1 = IDENTITY("Hello, World!");
identity_t example_2 = IDENTITY("Lorem Ipsum");
identity_t example_3 = IDENTITY("\"A");
identity_t example_4 = IDENTITY("A\"");
identity_t example_5 = IDENTITY("\"");
identity_t example_6 = IDENTITY("A");
#include <identity/undefine.h>

#include <identity/define.h>
identity_t example_7 = IDENTITY("com.company.product.b");
identity_t example_8 = IDENTITY("com.company.product.d");
int example_9 = IDENTITY_INT("com.company.product.b");
int example_10 = IDENTITY_INT("com.company.product.d");
#include <identity/undefine.h>

int main()
{
	assert(example_1 == 606330207822318758ULL);
	assert(example_2 == 2494223799487696ULL);
	assert(example_3 == 12920ULL);
	assert(example_4 == 20808ULL);
	assert(example_5 == 697ULL);
	assert(example_6 == 1258ULL);
	assert(example_7 == 17896281712065944250ULL);
	assert(example_8 == 17896281712065944284ULL);
	assert(example_9 == 134388410);
	assert(example_10 == 134388444);
	assert(example_3 != example_4);
	assert(example_5 != example_6);
	assert(example_3 != example_5);
	assert(example_4 != example_6);
	assert(example_7 != example_8);
	assert(example_9 != example_10);
	puts("Test Passed!");
	return 0;
}