/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:20 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/27 15:28:20 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	init_mapdata(t_mapdata *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
	return (1);
}

static int	check_required_elements(t_mapdata *map)
{
	if (!map->north_texture || !map->south_texture ||
		!map->west_texture || !map->east_texture)
	{
		ft_printf("Error\nMissing texture path(s)\n");
		return (0);
	}
	if (map->floor_color == -1 || map->ceiling_color == -1)
	{
		ft_printf("Error\nMissing floor or ceiling color\n");
		return (0);
	}
	if (map->player_x == -1 || map->player_y == -1 || !map->player_dir)
	{
		ft_printf("Error\nPlayer position not found or invalid\n");
		return (0);
	}
	if (!map->grid || map->height == 0 || map->width == 0)
	{
		ft_printf("Error\nInvalid or missing map\n");
		return (0);
	}
	return (1);
}

t_mapdata	*map_parser(char *filename)
{
	t_mapdata	*map;

	map = malloc(sizeof(t_mapdata));
	if (!map)
	{
		ft_printf("Error\nMemory allocation failed\n");
		return (NULL);
	}
	init_mapdata(map);
	if (!parse_elements(map, filename))
		return (free_mapdata(map), NULL);
	if (!parse_map_grid(map, filename))
		return (free_mapdata(map), NULL);
	if (!check_required_elements(map))
		return (free_mapdata(map), NULL);
	if (!validate_map(map))
		return (free_mapdata(map), NULL);
	return (map);
}

void	free_mapdata(t_mapdata *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->east_texture)
		free(map->east_texture);
	free(map);
}
