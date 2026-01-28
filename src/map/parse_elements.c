/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:58 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 12:40:10 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_empty_line(char *line)
{
	char	*trimmed;
	int		empty;

	if (!line || line[0] == '\n')
		return (1);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	empty = (ft_strlen(trimmed) == 0);
	free(trimmed);
	return (empty);
}

static int	is_map_start(char c)
{
	return (c == '1' || c == '0' || c == ' ');
}

static int	handle_element_line(t_mapdata *map, char *line, int *result)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		return (*result = parse_texture_line(map, line), 1);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (*result = parse_color_line(map, line), 1);
	return (0);
}

int	parse_elements(t_mapdata *map, char *filename)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nCannot open file: %s\n", filename), 0);
	line = get_next_line(fd);
	result = 1;
	while (line && result)
	{
		if (!is_empty_line(line) && is_map_start(line[0]))
			break ;
		if (!is_empty_line(line))
			handle_element_line(map, line, &result);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (result);
}
