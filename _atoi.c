#include "shell.h"

/**
 * synergic - The func should return true if the shell is in interactive mod
 * @tip: The address of the struct
 *
 * Return: 1 if synergic, else 0
 */
int synergic(tip_t *tip)
{
	return (isatty(STDIN_FILENO) && tip->readfd <= 2);
}

/**
 * is_separ – function evaluates whether a char is a separator
 * @d: the inputted character to be evaluated
 * @separ: separator string
 *
 * Return: 1 if true, else 0
 */
int is_separ(char d, char *separ)
{
	while (*separ)
		if (*separ++ == d)
			return (1);
	return (0);
}

/**
 * is_alpha - function evaluates whether a char is an alphabet
 * @d: the inputted character to be evaluated
 * Return: 1 if d is an alphabet, else 0
 */

int is_alpha(int d)
{
	if ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi – Function changes a string to an integer
 * @t: String to be changed
 *
 * Return: 0 if there are nums within string, else changed number
 */

int _atoi(char *t)
{
	int j, signal = 1, wave = 0, yield;
	unsigned int resu = 0;

	for (j = 0; t[j] != '\0' && wave != 2; j++)
	{
		if (t[j] == '-')
			signal *= -1;

		if (t[j] >= '0' && t[j] <= '9')
		{
			wave = 1;
			resu *= 10;
			resu += (t[j] - '0');
		}
		else if (wave == 1)
			wave = 2;
	}

	if (signal == -1)
		yield = -resu;
	else
		yield = resu;

	return (yield);
}

