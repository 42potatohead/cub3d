/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:42 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 12:10:36 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1');
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

static int	is_walkable(char c)
{
	return (c == '0');
}

/*
	// Check if walkable space is adjacent to void (outside map)
	// Since we convert all spaces to walls, we don't need to check for spaces
	// Just ensure walkable spaces are properly enclosed by walls
	investigate later ###
*/
static int	check_boundaries(t_mapdata *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_walkable(map->grid[i][j]))
			{
				if (i > 0 && j > 0 && i < map->height - 1 && j < map->width - 1)
				{
					if (!is_walkable(map->grid[i - 1][j]) && map->grid[i - 1][j] != '1')
					{
						ft_printf("Error\nMap not properly enclosed at (%d, %d)\n", i, j);
						return (0);
					}
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	flood_fill_check(t_mapdata *map, int x, int y, char **visited)
{
	if (x < 0 || x >= map->height || y < 0 || y >= map->width)
		return (0);
	if (visited[x][y] == '1' || map->grid[x][y] == '1')
		return (1);
	if (map->grid[x][y] == ' ')
		return (0);
	visited[x][y] = '1';
	if (!flood_fill_check(map, x + 1, y, visited)
		|| !flood_fill_check(map, x - 1, y, visited)
		|| !flood_fill_check(map, x, y + 1, visited)
		|| !flood_fill_check(map, x, y - 1, visited))
		return (0);
	return (1);
}

static char	**create_visited_grid(t_mapdata *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = malloc(map->width + 1);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j < map->width)
			visited[i][j++] = '0';
		visited[i][map->width] = '\0';
		i++;
	}
	return (visited);
}

static void	free_visited_grid(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static int	validate_map_enclosure(t_mapdata *map)
{
	char	**visited;
	int		result;

	visited = create_visited_grid(map);
	if (!visited)
		return (0);
	result = flood_fill_check(map, (int)map->player_y,
			(int)map->player_x, visited);
	if (!result)
		ft_printf("Error\nMap is not properly enclosed\n");
	free_visited_grid(visited, map->height);
	return (result);
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
	if (!validate_map_enclosure(map))
		return (0);
	if (!validate_textures_exist(map))
		return (0);
	return (1);
}
