#include "shell.h"

/**
 * main - Start point
 * @ac: arg counnt
 * @av: arg vectoor
 *
 * Return: 0 (success), else 1
 */
int main(int ac, char **av)
{
	tip_t tip[] = { TIP_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		tip->readfd = fd;
	}
	popult_env_list(tip);
	read_histry(tip);
	hsh(tip, av);
	return (EXIT_SUCCESS);
}
