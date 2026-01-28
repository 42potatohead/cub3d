/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:42 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 21:21:23 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ');
}

static int	validate_characters(t_mapdata *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i])
			return (ft_printf(
					"Error\nNull row found in map at row %d\n", i), 0);
		j = 0;
		while (j < map->width && map->grid[i][j])
		{
			if (!is_valid_char(map->grid[i][j]))
			{
				ft_printf("Error\nInvalid character '%c' in map at (%d, %d)\n",
					map->grid[i][j], i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_space(char c)
{
	return (c == ' ');
}

static int	validate_textures_exist(t_mapdata *map)
{
	int	fd;

	fd = open(map->north_texture, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nNorth texture file not found\n"), 0);
	close(fd);
	fd = open(map->south_texture, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nSouth texture file not found\n"), 0);
	close(fd);
	fd = open(map->west_texture, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nWest texture file not found\n"), 0);
	close(fd);
	fd = open(map->east_texture, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nEast texture file not found\n"), 0);
	close(fd);
	return (1);
}

int	validate_map(t_mapdata *map)
{
	if (!validate_characters(map))
		return (0);
	if (!check_boundaries(map))
		return (0);
	if (!validate_textures_exist(map))
		return (0);
	return (1);
}
