/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:05:03 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 12:03:37 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static int	find_player_position(t_mapdata *map, char *line, int row)
{
	int		col;

	col = 0;
	while (line[col])
	{
		if (line[col] == 'N' || line[col] == 'S'
			|| line[col] == 'E' || line[col] == 'W')
		{
			if (map->player_dir != 0)
			{
				ft_printf("Error\nMultiple player positions found\n");
				return (0);
			}
			map->player_x = col + 0.3;
			map->player_y = row + 0.3;
			map->player_dir = line[col];
			line[col] = '0';
		}
		col++;
	}
	return (1);
}

static char	*process_map_line(char *line, int target_width)
{
	char		*processed;
	char		*trimmed;
	size_t		i;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (NULL);
	processed = malloc(target_width + 1);
	if (!processed)
		return (free(trimmed), NULL);
	i = 0;
	while (trimmed && i < ft_strlen(trimmed))
	{
		if (trimmed[i] == ' ')
			processed[i] = '1';
		else
			processed[i] = trimmed[i];
		i++;
	}
	while (i < (size_t)target_width)
		processed[i++] = '1';
	processed[target_width] = '\0';
	free(trimmed);
	return (processed);
}

static int	update_max_width(int max_width, char *line)
{
	int	current_width;

	current_width = ft_strlen(line);
	if (current_width > 0 && line[current_width - 1] == '\n')
		current_width--;
	if (current_width > max_width)
		max_width = current_width;
	return (max_width);
}

static int	calculate_max_width(char *filename)
{
	int		fd;
	char	*line;
	int		max_width;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	max_width = 0;
	map_started = 0;
	while (read_next_line(fd, &line))
	{
		if (!map_started)
			map_started = (line[0] == '1' || line[0] == '0' || line[0] == ' ');
		if (map_started)
			max_width = update_max_width(max_width, line);
		free(line);
	}
	return (close(fd), max_width);
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

static int	skip_or_start_map(int *map_started, char *line)
{
	if (!*map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
		*map_started = 1;
	return (*map_started);
}

static int	is_nonempty_map_line(char *line)
{
	char	*trimmed;
	int		ok;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	ok = (ft_strlen(trimmed) > 0);
	free(trimmed);
	return (ok);
}

static int	process_and_store_row(t_mapdata *map, char *line, int row)
{
	if (!find_player_position(map, line, row))
		return (0);
	map->grid[row] = process_map_line(line, map->width);
	if (!map->grid[row])
		return (0);
	return (1);
}

int	read_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (0);
	return (1);
}

static int	handle_map_line(t_mapdata *map,
		char *line, int *row, int *map_started)
{
	if (!skip_or_start_map(map_started, line))
		return (1);
	if (!is_nonempty_map_line(line))
		return (1);
	if (!process_and_store_row(map, line, *row))
		return (0);
	(*row)++;
	return (1);
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
