#include "shell.h"

/**
 * _is_cmd - Func determns if a file is an exec_cmd
 * @tip: Tip_struct
 * @path: File_path
 *
 * Return: 1 on true, else 0
 */
int _is_cmd(tip_t *tip, char *path)
{
	struct stat st;

	(void)tip;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dup_chars - Func duplicate_chars
 * @pathstr: Path’s strng
 * @start: Beginng index
 * @stop: Endng index
 *
 * Return: Pointer to fresh buff
 */
char *_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * _find_path - Func find this comand in d PATH strng
 * @tip: Tip_struct
 * @pathstr: PATH_strng
 * @cmd: cmd to be found
 *
 * Return: The full path of cmd upon find else NULL
 */
char *_find_path(tip_t *tip, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_is_cmd(tip, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = _dup_chars(pathstr, curr_pos, j);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (_is_cmd(tip, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
