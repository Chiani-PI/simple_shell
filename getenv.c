#include "shell.h"

/**
 * _get_environ_ - returns the string array copy of our environ
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
char **_get_environ_(tip_t *tip)
{
	if (!tip->environ || tip->env_changed)
	{
		tip->environ = _list_to_strings(tip->env);
		tip->env_changed = 0;
	}

	return (tip->environ);
}

/**
 * un_setenv – Func rems an envir variabl
 * @tip: The struct containn possible args. For maintainn const func prototyp
 *  Return: 1 if deleted, else 0
 * @var: Envir varbl property’s strng
 */
int un_setenv(tip_t *tip, char *var)
{
	list_t *node = tip->env;
	size_t j = 0;
	char *po;

	if (!node || !var)
		return (0);

	while (node)
	{
		po = starts_with(node->str, var);
		if (po && *po == '=')
		{
			tip->env_changed = del_node_at_indx(&(tip->env), i);
			j = 0;
			node = tip->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (tip->env_changed);
}

/**
 * _set_env – Func inits a fresh envirnmnt varbl or mods a present one
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * @var: Envi varbl proprty of strng
 * @value: Envi varbl value of strng
 *  Return: Always 0
 */
int _set_env(tip_t *tip, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *po;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = tip->env;
	while (node)
	{
		po = starts_with(node->str, var);
		if (po && *po == '=')
		{
			free(node->str);
			node->str = buf;
			tip->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addd_nodde_endd(&(tip->env), buf, 0);
	free(buf);
	tip->env_changed = 1;
	return (0);
}
