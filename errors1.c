#include "shell.h"

/**
 * _erratoi – Func changes a str to an int
 * @t: String for conversion
 * Return: 0 if there’s no nums in the str, convertd num, else -1 (error)
 */
int _erratoi(char *t)
{
	int j = 0;
	unsigned long int resu = 0;

	if (*t == '+')
		t++;  /* TODO: Why does main return 255 on account of this? */
	for (j = 0;  t[j] != '\0'; j++)
	{
		if (t[j] >= '0' && t[j] <= '9')
		{
			resu *= 10;
			resu += (t[j] - '0');
			if (resu > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resu);
}

/**
 * priint_error - prints an error message
 * @tip: Param nd return informatn structur
 * @errstr: The string housing d specified err_type
 * Return: 0 if there’s no nums in the str, convertd num, else -1 (error)
 */
void priint_error(tip_t *tip, char *errstr)
{
	_eputs(tip->fname);
	_eputs(": ");
	priint_dec(tip->lne_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(tip->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * priint_dec - Func prints a dec (int) num (base10)
 * @input: Input
 * @fd: File-descriptr to be written to
 *
 * Return: Tnum of chars printd
 */
int priint_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abbs, present;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abbs = -input;
		__putchar('-');
		count++;
	}
	else
		_abbs = input;
	present = _abbs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abbs / j)
		{
			__putchar('0' + present / j);
			count++;
		}
		present %= j;
	}
	__putchar('0' + present);
	count++;

	return (count);
}

/**
 * transform_num – A convrtr func, clone of itoa
 * @num: Numeral
 * @base: The base
 * @waves: Arg flags
 *
 * Return: Str
 */
char *transform_num(long int num, int base, int waves)
{
	static char *array;
	static char buffer[50];
	char signal = 0;
	char *ptr;
	unsigned long nm = num;

	if (!(waves & CONVERT_UNSIGNED) && num < 0)
	{
		nm = -num;
		signal = '-';

	}
	array = waves & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[nm % base];
		nm /= base;
	} while (nm != 0);

	if (signal)
		*--ptr = signal;
	return (ptr);
}

/**
 * rem_comments - Func to replac d 1st instance of '#' with '\0'
 * @buf: Address of strng for mod
 *
 * Return: 0;
 */
void rem_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
