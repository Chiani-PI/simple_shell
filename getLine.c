#include "shell.h"

/**
 * _input_buf – The buffer’s_chaind_commnds
 * @tip: Param struct
 * @buf: Buffer addy
 * @len: Length variabl addy
 *
 * Return: Bytes reaad
 */
ssize_t _input_buf(tip_t *tip, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_pp = 0;

	if (!*len) /* Fill the buffer if nuffns left it */
	{
		/*bbfree((void **)tip->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_pp, stdin);
#else
		r = _get_line(tip, buf, &len_pp);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* rem trailng_newline */
				r--;
			}
			tip->lnecount_wave = 1;
			rem_comments(*buf);
			build_histry_list(tip, *buf, tip->histrycount++);
			/* If (str_chr(*buf, ';')), is it a commnd_chain? */
			{
				*len = r;
				tip->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _get_input – Func gets a line without new_line
 * @tip: Param struct
 *
 * Return: Bytes reaad
 */
ssize_t _get_input(tip_t *tip)
{
	static char *buf; /* The ';' commnd_chain_buffer */
	static size_t j, k, len;
	ssize_t r = 0;
	char **buf_pp = &(tip->arg), *po;

	_putchar(BUF_FLUSH);
	r = _input_buf(tip, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* There’re commnds remaining in the chain_buffer */
	{
		k = j; /* init fresh iteratr to present buf position */
		po = buf + j; /* get pointr 4r return */

		_check_chain(tip, buf, &k, j, len);
		while (k < len) /* iterte to semicln or end */
		{
			if (_is_chain(tip, buf, &k))
				break;
			k++;
		}

		j = k + 1; /* incrmnt past nulled ';'' */
		if (j >= len) /* Has buffer end reached? */
		{
			j = len = 0; /* reset positn & len */
			tip->cmd_buf_type = CMD_NORM;
		}

		*buf_pp = po; /* pass pointer back to present cmd positn */
		return (str_len(p)); /* return len of present cmd */
	}

	*buf_pp = buf; /* Except not a chain, pass buffer back from _get_line() */
	return (r); /* return buffer len frrom _get_line() */
}

/**
 * _read_buf – Func reads buffer
 * @tip: Param struct
 * @buf: Buffer
 * @j: Size
 *
 * Return: r
 */
ssize_t _read_buf(tip_t *tip, char *buf, size_t *j)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(tip->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*j = r;
	return (r);
}

/**
 * _get_line – Func gets nxt_line of input from STDIN
 * @tip: Param struct
 * @ptr: Pointer addy to buffer, preallocatd or NULL
 * @length: Size of preallocatd pointr buffr if not NULL
 *
 * Return: t
 */
int _get_line(tip_t *tip, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t l;
	ssize_t r = 0, t = 0;
	char *po = NULL, *new_pp = NULL, *d;

	po = *ptr;
	if (po && length)
		t = *length;
	if (j == len)
		j = len = 0;

	r = _read_buf(tip, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	d = str_chr(buf + j, '\n');
	l = d ? 1 + (unsigned int)(d - buf) : len;
	new_pp = _re_alloc(po, t, t ? t + l : l + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (po ? free(po), -1 : -1);

	if (t)
		strn_cat(new_pp, buf + j, l - j);
	else
		strn_cpy(new_pp, buf + i, k - i + 1);

	t += l - j;
	j = l;
	po = new_pp;

	if (length)
		*length = t;
	*ptr = po;
	return (t);
}

/**
 * _sigintHandler – Func to block ctrl-C
 * @sigg_num: the signal number
 *
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int sigg_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
