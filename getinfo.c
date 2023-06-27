#include "shell.h"

/**
 * clear_tip – Func inits tip_t struct
 * @tip: Struct addy
 */
void clear_tip(tip_t *tip)
{
	tip->arg = NULL;
	tip->argv = NULL;
	tip->path = NULL;
	tip->argc = 0;
}

/**
 * set_tip - Func inits tip_t struct
 * @tip: Struct addy
 * @av: Argt vectr
 */
void set_tip(tip_t *tip, char **av)
{
	int j = 0;

	tip->fname = av[0];
	if (tip->arg)
	{
		tip->argv = stritow(tip->arg, " \t");
		if (!tip->argv)
		{
			tip->argv = malloc(sizeof(char *) * 2);
			if (tip->argv)
			{
				tip->argv[0] = str_dup(tip->arg);
				tip->argv[1] = NULL;
			}
		}
		for (j = 0; tip->argv && tip->argv[j]; j++)
			;
		tip->argc = j;

		_replace_alias(tip);
		_replace_vars(tip);
	}
}

/**
 * free_tip – Func to free tip_t struct fields
 * @tip: Struct addy
 * @all: True if all fields are being freed
 */
void free_tip(tip_t *tip, int all)
{
	_ffree(tip->argv);
	tip->argv = NULL;
	tip->path = NULL;
	if (all)
	{
		if (!tip->cmd_buf)
			free(tip->arg);
		if (tip->env)
			_free_list(&(tip->env));
		if (tip->history)
			_free_list(&(tip->history));
		if (tip->alias)
			_free_list(&(tip->alias));
		_ffree(tip->environ);
			tip->environ = NULL;
		bbfree((void **)tip->cmd_buf);
		if (tip->readfd > 2)
			close(tip->readfd);
		_putchar(BUF_FLUSH);
	}
}
