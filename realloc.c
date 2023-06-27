#include "shell.h"

/**
 * _mem_set – Func fills memry with a const_byte
 * @s: Pointr to the mem_area
 * @b: Byte to_fill *s with
 * @n: Amnt of bytes_to be_filled
 * Return: (s) Pointer to s mem_area
 */
char *_mem_set(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * _ffree – Func to free a strng_of_strngs
 * @pp: strng_of_strngs
 */
void _ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _re_alloc – Func reallcts a mem_block
 * @ptr: Pointer to prev_ malloc'atd_block
 * @old_size: Byte sz of prev_block
 * @new_size: Byte sz of new_block
 *
 * Return: Pointer to da_ol'block_nameen.
 */
void *_re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *po;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	po = malloc(new_size);
	if (!po)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		po[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (po);
}
