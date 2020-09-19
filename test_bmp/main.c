#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_fd(char *s, int fd, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void ft_print_null(int nb, int fd)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd('\0', fd);
		i++;
	}
}

int main(int argc, char **argv)
{
	char chara_hexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int result;
	int number;
	char shlag[2];

	number = atoi(argv[1]);

	result = number / 16;
	shlag[0] = chara_hexa[number % 16];
	number = result;
	result = number / 16;
	shlag[1] = chara_hexa[number % 16];
	printf("CLIQUE CLAK: %c%c\n", shlag[1], shlag[0]);
	return (0);
}
