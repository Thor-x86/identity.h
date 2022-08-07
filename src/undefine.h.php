/*
<?php
	echo file_get_contents("./LICENSE");
?>
*/

#ifdef IDENTITY

#undef IDENTITY

<?php
	$max_iter = getenv("MAX_ITERATION");
	for ($i = 0; $i < $max_iter; $i++)
	{
		echo "#undef __IDENTITY_ITER_$i\n";
	}
?>

#undef __IDENTITY_HASH_FUNC

#endif // #ifdef IDENTITY