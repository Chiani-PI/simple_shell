#include "shell.h"

/**
 * addd_nodde – Func to addd_nodde to sttart¬_of_list
 * @head: Pointer_addy to head_node
 * @str: Strng_field of node
 * @num: Histrys node index
 *
 * Return: List sz
 */
list_t *addd_nodde(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_mem_set((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addd_nodde_endd – Func adds_node to end_of_list
 * @head: Pointer to head_node addy
 * @str: str_field of node
 * @num: histry_node index
 *
 * Return: List sz
 */
list_t *addd_nodde_endd(list_t **head, const char *str, int num)
{
	list_t *fresh_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	fresh_node = malloc(sizeof(list_t));
	if (!fresh_node)
		return (NULL);
	_mem_set((void *)fresh_node, 0, sizeof(list_t));
	fresh_node->num = num;
	if (str)
	{
		fresh_node->str = str_dup(str);
		if (!fresh_node->str)
		{
			free(fresh_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = fresh_node;
	}
	else
		*head = fresh_node;
	return (fresh_node);
}

/**
 * priint_list_str – Func prints only the str_elemnt of a list_t linked_list
 * @ho: Node1 pointer
 *
 * Return: List sz
 */
size_t priint_list_str(const list_t *ho)
{
	size_t j = 0;

	while (ho)
	{
		_puts(ho->str ? ho->str : "(nil)");
		_puts("\n");
		ho = ho->next;
		j++;
	}
	return (j);
}

/**
 * del_node_at_indx – Func delts_node at givn_index
 * @head: Node1 pointer addy
 * @index: Node_index for deletion
 *
 * Return: 1 (success), else 0
 */
int del_node_at_indx(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * _free_list – Func free_all_noddes of liist
 * @head_ptr: Head_node pointer addy
 *
 * Return: void
 */
void _free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
