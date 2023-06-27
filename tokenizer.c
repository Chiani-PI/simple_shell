#include "shell.h"

/**
 * **stritow – Func splits_string into_words. Repete separators are ignrd
 * @str: Input_strng
 * @deli: Separ_strng
 * Return: Pointer to an arr_strngs, else NULL if fail
 */

char **stritow(char *str, char *e)
{
	int j, k, l, n, numeralwords = 0;
	char **t;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_separ(str[j], e) && (is_separ(str[j + 1], e) || !str[j + 1]))
			numeralwords++;

	if (numeralwords == 0)
		return (NULL);
	t = malloc((1 + numeralwords) * sizeof(char *));
	if (!t)
		return (NULL);
	for (j = 0, k = 0; k < numeralwords; k++)
	{
		while (is_separ(str[j], e))
			j++;
		l = 0;
		while (!is_separ(str[j + l], e) && str[j + l])
			l++;
		t[k] = malloc((l + 1) * sizeof(char));
		if (!t[k])
		{
			for (l = 0; l < k; l++)
				free(t[l]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			t[k][n] = str[j++];
		t[k][n] = 0;
	}
	t[k] = NULL;
	return (t);
}

/**
 * **stritow2 – Func splits strng_into_words
 * @str: Input_strng
 * @deli: Separ
 * Return: Pointr to an array_of_strngs, else NULL if fail
 */
char **stritow2(char *str, char e)
{
	int j, k, l, n, numeralwords = 0;
	char **t;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		if ((str[j] != e && str[j + 1] == e) ||
				    (str[j] != e && !str[j + 1]) || str[j + 1] == e)
			numeralwords++;
	if (numeralwords == 0)
		return (NULL);
	t = malloc((1 + numeralwords) * sizeof(char *));
	if (!t)
		return (NULL);
	for (j = 0, k = 0; k < numeralwords; k++)
	{
		while (str[j] == e && str[j] != e)
			j++;
		l = 0;
		while (str[j + l] != e && str[j + l] && str[j + l] != e)
			l++;
		t[k] = malloc((l + 1) * sizeof(char));
		if (!t[k])
		{
			for (l = 0; l < k; l++)
				free(t[]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			t[k][n] = str[j++];
		t[k][n] = 0;
	}
	t[k] = NULL;
	return (t);
}
