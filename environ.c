#include "shell.h"

/**
 * _ourenv - Func to print present env
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
int _ourenv(tip_t *tip)
{
	priint_list_str(tip->env);
	return (0);
}

/**
 * get_env - Func to get d vlue of an envirnmnt variabl
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * @name: The envirnmnt variabl’s name
 *
 * Return: Vlue of d envirnmnt variabl
 */
char *get_env(tip_t *tip, const char *name)
{
	list_t *node = tip->env;
	char *po;

	while (node)
	{
		po = starts_with(node->str, name);
		if (po && *po)
			return (po);
		node = node->next;
	}
	return (NULL);
}

/**
 * our_setenv - Func to init a fresh envirnmnt variabl or mod an existn var
 * @tip: The struct containn possible args. For maintainn const func prototyp
 *  Return: 0
 */
int our_setenv(tip_t *tip)
{
	if (tip->argc != 3)
	{
		_eputs("Num of arguments is incorrect\n");
		return (1);
	}
	if (_set_env(tip, tip->argv[1], tip->argv[2]))
		return (0);
	return (1);
}

/**
 * our_unsetenv - Func to remv an envirnmnt varbl
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
int our_unsetenv(tip_t *tip)
{
	int j;

	if (tip->argc == 1)
	{
		_eputs("Arguments are too few\n");
		return (1);
	}
	for (j = 1; j <= tip->argc; j++)
		un_setenv(tip, tip->argv[j]);

	return (0);
}

/**
 * popult_env_list - Func will populate an envrnmnt linked_list
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
int popult_env_list(tip_t *tip)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		addd_nodde_endd(&node, environ[j], 0);
	tip->env = node;
	return (0);
}
