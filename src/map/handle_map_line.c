/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:58:43 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 13:06:19 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

static int	process_and_store_row(t_mapdata *map, char *line, int row)
{
	if (!find_player_position(map, line, row))
		return (0);
	map->grid[row] = process_map_line(line, map->width);
	if (!map->grid[row])
		return (0);
	return (1);
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

static int	skip_or_start_map(int *map_started, char *line)
{
	if (!*map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
		*map_started = 1;
	return (*map_started);
}

int	handle_map_line(t_mapdata *map,
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
