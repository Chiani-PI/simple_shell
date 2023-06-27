#include "shell.h"

/**
 * _ourhistry – Func shows history_ls, a command each ln,
 * preceded by ln nums from 0
 * @tip: The struct containn possible args. For maintainn const func prototyp
 *  Return: 0
 */
int _ourhistry(tip_t *tip)
{
	priint_list(tip->history);
	return (0);
}

/**
 * un_set_allias – Func to (un)assign an alias from a strriinng
 * @tip: Struct for param
 * @str: String’s allias
 *
 * Return: 0 (Success), else 1
 */
int un_set_allias(tip_t *tip, char *str)
{
	char *po, d;
	int retu;

	po = str_chr(str, '=');
	if (!po)
		return (1);
	d = *po;
	*po = 0;
	retu = del_node_at_indx(&(tip->alias),
		_get_node_index(tip->alias, _node_starts_with(tip->alias, str, -1)));
	*po = d;
	return (retu);
}

/**
 * seet_allias - Func to assign an alias to a strriinng
* @tip: Struct for param
 * @str: String’s allias
 *
 * Return: 0 (Success), else 1
 */
int seet_allias(tip_t *tip, char *str)
{
	char *po;

	po = str_chr(str, '=');
	if (!po)
		return (1);
	if (!*++po)
		return (un_set_allias(tip, str));

	un_set_allias(tip, str);
	return (addd_nodde_endd(&(tip->alias), str, 0) == NULL);
}

/**
 * priint_allias – Func to print a string’s alias
 * @node: Allias’ node
 *
 * Return: 0 (success), else 1
 */
int priint_allias(list_t *node)
{
	char *po = NULL, *ab = NULL;

	if (node)
	{
		po = str_chr(node->str, '=');
		for (ab = node->str; ab <= po; ab++)
		_putchar(*ab);
		_putchar('\'');
		_puts(po + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ourallias – Func copies the built-in allias ”((man alias))”
 * @tip: The struct containn possible args. For maintainn const func prototyp
 *  Return: 0
 */
int _ourallias(tip_t *tip)
{
	int j = 0;
	char *po = NULL;
	list_t *node = NULL;

	if (tip->argc == 1)
	{
		node = tip->alias;
		while (node)
		{
			priint_allias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; tip->argv[j]; j++)
	{
		po = str_chr(tip->argv[j], '=');
		if (po)
			seet_allias(tip, tip->argv[j]);
		else
			priint_allias(_node_starts_with(tip->alias, tip->argv[j], '='));
	}

	return (0);
}
