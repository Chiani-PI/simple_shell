#include "shell.h"

/**
 * _is_chain - Func checks if present_char in buffer is a chain_sepasr
 * @tip: Param_struct
 * @buf: Char_buffer
 * @po: Present position in buf addy
 *
 * Return: 1 if chain_separ, else 0
 */
int _is_chain(tip_t *tip, char *buf, size_t *po)
{
	size_t k = *po;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		tip->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		tip->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* End of present cmd found */
	{
		buf[k] = 0; /* Swap semi-colon with null */
		tip->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*po = k;
	return (1);
}

/**
 * _check_chain - Func confirms if chainng shld cont dependng on prev status
 * @tip: Param_struct
 * @buf: Char_buffer
 * @po: Addy_present positn in buf
 * @i: StartN_positn in buf
 * @len: buf_len
 *
 * Return: Void
 */
void _check_chain(tip_t *tip, char *buf, size_t *po, size_t i, size_t len)
{
	size_t j = *po;

	if (tip->cmd_buf_type == CMD_AND)
	{
		if (tip->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (tip->cmd_buf_type == CMD_OR)
	{
		if (!tip->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*po = j;
}

/**
 * _replace_alias - Func replace_aliases in tokenzd_strng
 * @tip: Param_struct
 *
 * Return: 1 on replace, else 0
 */
int _replace_alias(tip_t *tip)
{
	int j;
	list_t *node;
	char *po;

	for (j = 0; j < 10; j++)
	{
		node = _node_starts_with(tip->alias, tip->argv[0], '=');
		if (!node)
			return (0);
		free(tip->argv[0]);
		po = str_chr(node->str, '=');
		if (!po)
			return (0);
		po = str_dup(po + 1);
		if (!po)
			return (0);
		tip->argv[0] = po;
	}
	return (1);
}

/**
 * _replace_vars - Func replace_vars in tokenzd_strng
 * @tip: Param_struct
 *
 * Return: 1 on replace, else 0
 */
int _replace_vars(tip_t *tip)
{
	int j = 0;
	list_t *node;

	for (j = 0; tip->argv[j]; j++)
	{
		if (tip->argv[j][0] != '$' || !tip->argv[j][1])
			continue;

		if (!_strcmp(tip->argv[j], "$?"))
		{
			_replace_string(&(tip->argv[j]),
					str_dup(transform_num(tip->status, 10, 0)));
			continue;
		}
		if (!_strcmp(tip->argv[j], "$$"))
		{
			_replace_string(&(tip->argv[j]),
					str_dup(transform_num(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts_with(tip->env, &tip->argv[j][1], '=');
		if (node)
		{
			_replace_string(&(tip->argv[j]),
					str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&tip->argv[j], str_dup(""));

	}
	return (0);
}

/**
 * _replace_string - Func replace_strng
 * @old: Old strng_addy
 * @new: Fresh_strng
 *
 * Return: 1 on replace, else 0
 */
int _replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
