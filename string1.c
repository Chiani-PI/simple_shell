#include "shell.h"

/**
 * str_cpy - Func to copy strng
 * @dest: Desti
 * @src: Sourc
 *
 * Return: Pointr to desti
 */
char *str_cpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * str_dup - Func to dup_strng
 * @str: Strng for dup
 *
 * Return: Pointr to the dup_strng
 */
char *str_dup(const char *str)
{
	int length = 0;
	char *retu;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	retu = malloc(sizeof(char) * (length + 1));
	if (!retu)
		return (NULL);
	for (length++; length--;)
		retu[length] = *--str;
	return (retu);
}

/**
 * _puts - Func displays an input_strng
 * @str: Strng to be displayed
 *
 * Return: Nada
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - Func writes the char d to stdout
 * @d: Char for printing
 *
 * Return: 1 (success), else -1 and errno is set correctly.
 */
int _putchar(char d)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}
