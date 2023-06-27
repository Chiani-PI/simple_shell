#include "shell.h"

/**
 * strn_cpy – Func copies strng
 * @desti: Destinatn strng will be copied to
 * @src: Srce strng
 * @tn: Amount of char for copy
 * Return: Concatntd str
 */
char *strn_cpy(char *desti, char *src, int tn)
{
	int j, k;
	char *t = desti;

	j = 0;
	while (src[j] != '\0' && j < tn - 1)
	{
		desti[j] = src[j];
		k++;
	}
	if (j < tn)
	{
		k = j;
		while (k < tn)
		{
			desti[k] = '\0';
			k++;
		}
	}
	return (t);
}

/**
 * strn_cat – Func concats 2strings
 * @desti: String1
 * @src: String2
 * @tn: Tamount of bytes for max use
 * Return: Concatntd stri
 */
char *strn_cat(char *desti, char *src, int tn)
{
	int j, k;
	char *t = desti;

	j = 0;
	k = 0;
	while (desti[j] != '\0')
		j++;
	while (src[k] != '\0' && k < tn)
	{
		desti[j] = src[k];
		j++;
		k++;
	}
	if (k < tn)
		desti[j] = '\0';
	return (t);
}

/**
 * str_chr – Func finds char within strng
 * @t: String for parsing
 * @d: Character for search
 * Return: pointer to the memory_area t (t)
 */
char *str_chr(char *t, char d)
{
	do {
		if (*t == d)
			return (t);
	} while (*t++ != '\0');

	return (NULL);
}
