#include "shell.h"

/**
 * hsh - Func for the main shell_loop
 * @tip: Param and return_info structs
 * @av: Arg_vecor frm main()
 *
 * Return: 0 (success), else 1 or err_code
 */
int hsh(tip_t *tip, char **av)
{
	ssize_t r = 0;
	int builtin_retu = 0;

	while (r != -1 && builtin_retu != -2)
	{
		clear_tip(tip);
		if (synergic(tip))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = _get_input(tip);
		if (r != -1)
		{
			set_tip(tip, av);
			builtin_retu = _find_builtin(tip);
			if (builtin_retu == -1)
				_find_cmd(tip);
		}
		else if (synergic(tip))
			_putchar('\n');
		free_tip(tip, 0);
	}
	write_histry(tip);
	free_tip(tip, 1);
	if (!synergic(tip) && tip->status)
		exit(tip->status);
	if (builtin_retu == -2)
	{
		if (tip->err_num == -1)
			exit(tip->status);
		exit(tip->err_num);
	}
	return (builtin_retu);
}

/**
 * _find_builtin - Func searches for builtin_cmd
 * @tip: Param and return_info structs
 *
 * Return: -1 if builtin_not_found, 0 if builtin_exec_sucsfly,
 * 1 if builtin_found_ bt_unsucsfl, 2 if builtin_signals_exit()
 */
int _find_builtin(tip_t *tip)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _dexit},
		{"env", _ourenv},
		{"help", _myassist},
		{"history", _ourhistry},
		{"setenv", our_setenv},
		{"unsetenv", our_unsetenv},
		{"cd", _ourcd},
		{"alias", _ourallias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(tip->argv[0], builtintbl[j].type) == 0)
		{
			tip->lne_count++;
			built_in_ret = builtintbl[j].func(tip);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd - Func searches for cmd_in_PATH
 * @tip: Param and return_info structs
 *
 * Return: void
 */
void _find_cmd(tip_t *tip)
{
	char *path = NULL;
	int j, l;

	tip->path = tip->argv[0];
	if (tip->lnecount_wave == 1)
	{
		tip->lne_count++;
		tip->lnecount_wave = 0;
	}
	for (j = 0, l = 0; tip->arg[j]; j++)
		if (!is_separ(tip->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = _find_path(tip, get_env(tip, "PATH="), tip->argv[0]);
	if (path)
	{
		tip->path = path;
		_fork_cmd(tip);
	}
	else
	{
		if ((synergic(tip) || get_env(tip, "PATH=")
					|| tip->argv[0][0] == '/') && _is_cmd(tip, tip->argv[0]))
			_fork_cmd(tip);
		else if (*(tip->arg) != '\n')
		{
			tip->status = 127;
			priint_error(tip, "Not found\n");
		}
	}
}

/**
 * _fork_cmd - Func will fork exe_thread to run_cmd
 * @tip: Param and return_info structs
 *
 * Return: void
 */
void _fork_cmd(tip_t *tip)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* For TODO: PUT_ERR_FUNC sections */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(tip->path, tip->argv, _get_environ_(tip)) == -1)
		{
			free_tip(tip, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* For TODO: PUT_ERR_FUNC sections */
	}
	else
	{
		wait(&(tip->status));
		if (WIFEXITED(tip->status))
		{
			tip->status = WEXITSTATUS(tip->status);
			if (tip->status == 126)
				priint_error(tip, "Permission denied\n");
		}
	}
}
