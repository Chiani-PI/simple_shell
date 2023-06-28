#include "shell.h"

/**
 * str_len - Func will return str_length
 * @t: Strng for length_check
 *
 * Return: int for string_length
 */
int str_len(char *t)
{
	int j = 0;

	if (!t)
		return (0);

	while (*t++)
		j++;
	return (j);
}

/**
 * _strcmp - Func does dictionary analogy of two_strngs.
 * @t1: String1
 * @t2: String2
 *
 * Return: nega_tive if t1 less_than t2,
 * posi_tive if t1 greater_than t2, zero0 if t1 is_equal_to t2
 */
int _strcmp(char *t1, char *t2)
{
	while (*t1 && *t2)
	{
		if (*t1 != *t2)
			return (*t1 - *t2);
		t1++;
		t2++;
	}
	if (*t1 == *t2)
		return (0);
	else
		return (*t1 < *t2 ? -1 : 1);
}

/**
 * starts_with - Func evaluates if sewpin starts with yahstack
 * @yahstack: Strng to be search with
 * @sewpin: Substrng to be found
 *
 * Return: Addy of nxt_yahstack_char or NULL
 */
char *starts_with(const char *yahstack, const char *sewpin)
{
	while (*sewpin)
		if (*sewpin++ != *yahstack++)
			return (NULL);
	return ((char *)yahstack);
}

/**
 * str_cat - Func concatjoins two_strngs
 * @dest: Desti_buffer
 * @src: Src_buffer
 *
 * Return: Pointer to desti_buffer
 */
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
