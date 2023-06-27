#include "shell.h"

/**
 * _dexit – Function leaves shell
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: Exit shsowing its status, else 0 if tip.argv[0] isnt equalto exit
 */
int _dexit(tip_t *tip)
{
	int lvcheck;

	if (tip->argv[1]) /* only occurs when an exit arg is present*/
	{
		lvcheck = _erratoi(tip->argv[1]);
		if (lvcheck == -1)
		{
			tip->status = 2;
			priint_error(tip, "Illegal number: ");
			_eputs(tip->argv[1]);
			_eputchar('\n');
			return (1);
		}
		tip->err_num = _erratoi(tip->argv[1]);
		return (-2);
	}
	tip->err_num = -1;
	return (-2);
}

/**
 * _ourcd – Func switches the present dir of the process
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
int _ourcd(tip_t *tip)
{
	char *t, *dir, buffer[1024];
	int ch_dir_retu;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!tip->argv[1])
	{
		dir = get_env(tip, "HOME=");
		if (!dir)
			ch_dir_retu = /* TODO: What is this sup to be? */
				chdir((dir = get_env(tip, "PWD=")) ? dir : "/");
		else
			ch_dir_retu = chdir(dir);
	}
	else if (_strcmp(tip->argv[1], "-") == 0)
	{
		if (!get_env(tip, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(tip, "OLDPWD=")), _putchar('\n');
		ch_dir_retu = /* TODO: What is this sup to be? */
			chdir((dir = get_env(tip, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir_retu = chdir(tip->argv[1]);
	if (ch_dir_retu == -1)
	{
		priint_error(tip, "Unable to change directory to ");
		_eputs(tip->argv[1]), _eputchar('\n');
	}
	else
	{
		_set_env(tip, "OLDPWD", get_env(tip, "PWD="));
		_set_env(tip, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myassist - Func switches the present dir of the process
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * Return: 0
 */
int _myassist(tip_t *tip)
{
	char **arg_array;

	arg_array = tip->argv;
	_puts("This help call works. Function isn’t yet been implemented \n");
	if (0)
		_puts(*arg_array); /* temp alt_notused alternative */
	return (0);
}
