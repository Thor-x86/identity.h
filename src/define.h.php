/*
<?php
	echo file_get_contents("./LICENSE");
?>
*/

#ifndef __IDENTITY_TYPE_DEFINED
#define __IDENTITY_TYPE_DEFINED

typedef const unsigned long long identity_t;

#endif // #ifndef __IDENTITY_TYPE_DEFINED

#ifndef IDENTITY

#include <limits.h>

#define __IDENTITY_HASH_FUNC(s, n, i, x) (s[i < n ? n - 1 - i : 0] ^ x) * 17ull

<?php
	$max_iter = getenv("MAX_ITERATION");
	$last_iter = $max_iter - 1;

	echo "#define __IDENTITY_ITER_$last_iter(s, x, n) x\n";

	for ($i = $last_iter - 1; $i >= 0; $i--)
	{
		$next_iter = $i + 1;
		echo "#define __IDENTITY_ITER_$i(s, x, n) ($i < n ? __IDENTITY_HASH_FUNC(s, n, $i, __IDENTITY_ITER_$next_iter(s, x, n)) : x)\n";
	}
?>

#define IDENTITY(text) ((identity_t) /* */ __IDENTITY_ITER_0(text, 11ull, (sizeof text - 1)))

#define IDENTITY_INT(text) ((int)(__IDENTITY_ITER_0(text, 11ull, (sizeof text - 1)) & UINT_MAX))

#endif // #ifndef IDENTITY