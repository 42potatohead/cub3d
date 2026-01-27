/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:17:00 by zabu-bak         #+#    #+#             */
/*   Updated: 2026/01/26 17:17:00 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	count = 0;
	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
			map_started = 1;
		if (map_started && ft_strlen(ft_strtrim(line, " \t\n")) > 0)
			count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int	find_player_position(t_mapdata *map, char *line, int row)
{
	int		col;

	col = 0;
	while (line[col])
	{
		if (line[col] == 'N' || line[col] == 'S' ||
			line[col] == 'E' || line[col] == 'W')
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
	char	*processed;
	char	*trimmed;
	int		len;
	int		i;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (NULL);
	len = ft_strlen(trimmed);
	processed = malloc(target_width + 1);
	if (!processed)
	{
		free(trimmed);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		// Convert spaces to walls in the map section
		if (trimmed[i] == ' ')
			processed[i] = '1';
		else
			processed[i] = trimmed[i];
		i++;
	}
	while (i < target_width)
	{
		processed[i] = '1';  // Fill remaining space with walls
		i++;
	}
	processed[target_width] = '\0';
	free(trimmed);
	return (processed);
}

static int	calculate_max_width(char *filename)
{
	int		fd;
	char	*line;
	int		max_width;
	int		map_started;
	int		current_width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	max_width = 0;
	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
			map_started = 1;
		if (map_started)
		{
			current_width = ft_strlen(line);
			if (line[current_width - 1] == '\n')
				current_width--;
			if (current_width > max_width)
				max_width = current_width;
		}
		free(line);
	}
	close(fd);
	return (max_width);
}

int	parse_map_grid(t_mapdata *map, char *filename)
{
	int		fd;
	char	*line;
	int		row;
	int		map_started;

	map->height = count_map_lines(filename);
	if (map->height == 0)
	{
		ft_printf("Error\nNo map found\n");
		return (0);
	}
	map->width = calculate_max_width(filename);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	row = 0;
	map_started = 0;
	// Initialize all grid pointers to NULL first
	int i = 0;
	while (i <= map->height)
	{
		map->grid[i] = NULL;
		i++;
	}
	
	while ((line = get_next_line(fd)) && row < map->height)
	{
		if (!map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
			map_started = 1;
		if (map_started)
		{
			char *trimmed = ft_strtrim(line, " \t\n");
			if (trimmed && ft_strlen(trimmed) > 0)
			{
				free(trimmed);
				if (!find_player_position(map, line, row))
				{
					free(line);
					close(fd);
					return (0);
				}
				map->grid[row] = process_map_line(line, map->width);
				if (!map->grid[row])
				{
					free(line);
					close(fd);
					return (0);
				}
				row++;
			}
			else
			{
				if (trimmed)
					free(trimmed);
			}
		}
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	map->height = row; // Update height to actual number of rows processed
	return (1);
}
