#include "shell.h"

/**
 * _list_len - Func determns linked_list len
 * @ho: Node1 pointer
 *
 * Return: List sz
 */
size_t _list_len(const list_t *ho)
{
	size_t j = 0;

	while (ho)
	{
		ho = ho->next;
		j++;
	}
	return (j);
}

/**
 * _list_to_strings - Func returns arr_of_strngs of list->str
 * @head: Node1 pointer
 *
 * Return: arr_of_strngs
 */
char **_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = _list_len(head), k;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * priint_list - Func prints all_elem of a list_t linkd_list
 * @ho: Node1 pointer
 *
 * Return: List sz
 */
size_t priint_list(const list_t *ho)
{
	size_t j = 0;

	while (ho)
	{
		_puts(transform_num(ho->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ho->str ? ho->str : "(nil)");
		_puts("\n");
		ho = ho->next;
		j++;
	}
	return (j);
}

/**
 * _node_starts_with - Func returns_node whse_strng begins_with_prefix
 * @node: List head pointr
 * @prefix: Strng for matching
 * @d: Nxt char after prefix to_be matched
 *
 * Return: Matched node else null
 */
list_t *_node_starts_with(list_t *node, char *prefix, char d)
{
	char *po = NULL;

	while (node)
	{
		po = starts_with(node->str, prefix);
		if (po && ((d == -1) || (*po == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index - gets the index of a node
 * @head: List head pointr
 * @node: Node pointr
 *
 * Return: Node index oorr -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
