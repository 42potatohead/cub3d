/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:28:18 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 12:28:19 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_av(int ac, char **av, int fd)
{
	char	*last_char;

	if (ac == 2)
	{
		last_char = ft_substr(av[1], (ft_strlen(av[1]) - 4), 4);
		if (ft_strncmp(".cub", last_char, 4))
		{
			ft_printf("Error\nInvalid file type, Please try again later.\n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		if (fd == -1)
		{
			ft_printf("Error\nFile does not exist\n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		close(fd);
		free(last_char);
	}
	else
	{
		ft_printf("Error\nWrong number of arguments.\n");
		exit(EXIT_FAILURE);
	}
}
