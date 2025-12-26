#include "cub3d.h"

// TODO: pull and add libft and configure Makefile 

void	ft_check_av(int ac, char **av, int fd)
{
	char	*last_char;

	if (ac == 2)
	{
		last_char = ft_substr(av[1], (ft_strlen(av[1]) - 4), 4);
		if (ft_strncmp(".cub", last_char, 4))
		{
			ft_printf("Invalid file type, Please try again later. \n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		if (fd == -1)
		{
			ft_printf("File does not exist \n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		close(fd);
		free(last_char);
	}
	else
	{
		ft_printf("wrong number arguments, Please try again later. \n");
		exit(EXIT_FAILURE);
	}
}
