/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:05:03 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/29 20:12:29 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;
	int		map_started;
	char	*trimmed_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && (line[0] == '1'
				|| line[0] == '0' || line[0] == ' '))
			map_started = 1;
		trimmed_line = ft_strtrim(line, " \t\n");
		if (trimmed_line && map_started && ft_strlen(trimmed_line) > 0)
			count++;
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), count);
}

static void	init_grid_null(char **grid, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		grid[i] = NULL;
		i++;
	}
}

static int	parse_map_loop(t_mapdata *map, int fd)
{
	char	*line;
	int		row;
	int		map_started;

	row = 0;
	map_started = 0;
	while (row < map->height)
	{
		if (!read_next_line(fd, &line))
			break ;
		if (!handle_map_line(map, line, &row, &map_started))
			return (free(line), 0);
		free(line);
	}
	map->height = row;
	return (1);
}

int	parse_map_grid(t_mapdata *map, char *filename)
{
	int	fd;

	map->height = count_map_lines(filename);
	if (map->height == 0)
		return (ft_printf("Error\nNo map found\n"), 0);
	map->width = calculate_max_width(filename);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	init_grid_null(map->grid, map->height);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!parse_map_loop(map, fd))
		return (close(fd), 0);
	close(fd);
	return (1);
}
