#include "shell.h"

/**
 * get_histry_fl – Func gets d history_file
 * @tip: Param struct
 *
 * Return: The allctd strng which contains history_file
 */

char *get_histry_fl(tip_t *tip)
{
	char *buf, *dir;

	dir = get_env(tip, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_histry – Func creates a file or adds to a present file
 * @tip: Param struct
 *
 * Return: 1 (success), else -1
 */
int write_histry(tip_t *tip)
{
	ssize_t fd;
	char *filename = get_histry_fl(tip);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = tip->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_histry – Func readds histry 4rm file
 * @tip: Param struct
 *
 * Return: histrycount (success), else 0
 */
int read_histry(tip_t *tip)
{
	int j, last = 0, lnecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_histry_fl(tip);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_histry_list(tip, buf + last, lnecount++);
			last = j + 1;
		}
	if (last != j)
		build_histry_list(tip, buf + last, lnecount++);
	free(buf);
	tip->histrycount = lnecount;
	while (tip->histrycount-- >= HIST_MAX)
		del_node_at_indx(&(tip->history), 0);
	re_num_histry(tip);
	return (tip->histrycount);
}

/**
 * build_histry_list – Func adds_entry to a histry_linked_list
 * @tip: The struct containn possible args. For maintainn const func prototyp
 * @buf: buffer
 * @lnecount: History_lnecount or histrycount
 *
 * Return: 0
 */
int build_histry_list(tip_t *tip, char *buf, int lnecount)
{
	list_t *node = NULL;

	if (tip->history)
		node = tip->history;
	addd_nodde_endd(&node, buf, lnecount);

	if (!tip->history)
		tip->history = node;
	return (0);
}

/**
 * re_num_histry – Func renumbers histry_lniked_list following mod
 * @tip: The struct containn possible args. For maintainn const func prototyp
 *
 * Return: Fresh histrycount
 */
int re_num_histry(tip_t *tip)
{
	list_t *node = tip->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (tip->histrycount = j);
}
