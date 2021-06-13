#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <sys/resource.h>
#include <stdio.h>

static void ft_putstr(char *str)
{
	size_t len = ft_strlen(str);
	write(1, str, len);
}

int main (void)
{
	char	*line = NULL;
	int		result;
	int		fd;
	//printf("FD_SETSIZE: %d\n", FD_SETSIZE);

	fd = open("./main.c", O_RDONLY | O_CREAT);
	//fd = 1;

	while (1)
	{
		result = get_next_line(fd, &line);
		if (result == 1)
		{
			ft_putstr("nova linha: ");
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
			continue ;
		}
		else if (result == 0)
		{
			ft_putstr("nova linha: ");
			ft_putstr(line);
			ft_putstr("\n");
			ft_putstr("---- Nice, lemos tudo.\n");
			free(line);
		}
		else if (result == -1)
			ft_putstr("---- -1: Retornou erro\n");
		break ;

	}

	return (0);
	while (1)
	{
		result = get_next_line(0, &line);
		if (result == 1)
		{
			ft_putstr("Voce esta se sentindo assim: ");
			ft_putstr(line);
			ft_putstr("\n");
			free(line);
		}
		else 
			break;
	}
	ft_putstr("Essa linha vem depois do CTRL-D\n");
}
