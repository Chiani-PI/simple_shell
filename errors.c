#include "shell.h"

/**
 * _eputs – Func to print a string inputted
 * @str: String for printng
 *
 * Return: Nada
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar – Func to write d char d to standarderr
 * @d: Char for printng
 *
 * Return: 1(success), else -1 and d errno is appropriatly set
 */
int _eputchar(char d)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}

/**
 * _putfd – Func to write d char d to d given file_descriptr
 * @d: Char for printng
 * @fd: File-descriptr to be written to
 *
 * Return: 1 (success), else -1 and the errno is appropriatly set
 */
int _putfd(char d, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}

/**
 * _putsfd - Func to print a string inputted to a givn fd
 * @str: String for printng
 * @fd: File-descriptr to be written to
 *
 * Return: D Tnum of characterss printed to fd
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
