/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:42 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 16:34:40 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

// static int	is_walkable(char c)
// {
// 	return (c == '0');
// }

static int	is_space(char c)
{
	return (c == ' ');
}

static size_t	row_len_safe(char *row)
{
	if (!row)
		return (0);
	return (ft_strlen(row));
}

static char	get_cell(t_mapdata *map, int r, int c)
{
	size_t	len;

	if (!map || !map->grid || r < 0 || r >= map->height)
		return (' ');
	if (!map->grid[r])
		return (' ');
	len = row_len_safe(map->grid[r]);
	if (c < 0 || (size_t)c >= len)
		return (' ');
	return (map->grid[r][c]);
}

static int	validate_map_perimeter(t_mapdata *map)
{
	int		r;
	int		c;
	size_t	len;
	int		first_idx;
	int		last_idx;

	if (!map || !map->grid || map->height <= 0)
		return (0);
	r = 0;
	while (r < map->height)
	{
		if (!map->grid[r])
			return (ft_printf("Error\nNull row found in map at row %d\n", r), 0);
		len = row_len_safe(map->grid[r]);
		c = 0;
		while ((size_t)c < len)
		{
			first_idx = 0;
			while ((size_t)first_idx < len && is_space(map->grid[r][first_idx]))
				first_idx++;
			last_idx = (int)len - 1;
			while (last_idx >= 0 && is_space(map->grid[r][last_idx]))
				last_idx--;

			/* If top/bottom row: ignore leading whitespace, then only '1' or ' ' */
			if (r == 0 || r == map->height - 1)
			{
				if ((size_t)c >= (size_t)first_idx
					&& map->grid[r][c] != '1' && map->grid[r][c] != ' ')
					return (ft_printf("Error\nMap border row %d has invalid char '%c' at col %d\n",
							r, map->grid[r][c], c), 0);
			}
			else
			{
				/* Else: first and last non-space must be '1' (if any non-space exists) */
				if (last_idx >= first_idx)
				{
					if (map->grid[r][first_idx] != '1')
						return (ft_printf("Error\nRow %d must start with wall '1' after leading spaces\n", r), 0);
					if (map->grid[r][last_idx] != '1')
						return (ft_printf("Error\nRow %d must end with wall '1'\n", r), 0);
				}

				/*
				** If current row longer than row above/below and we're past their length,
				** current char must be '1'
				*/
				if ((size_t)c >= row_len_safe(map->grid[r - 1])
					&& row_len_safe(map->grid[r]) > row_len_safe(map->grid[r - 1]))
				{
					if (map->grid[r][c] != '1')
						return (ft_printf("Error\nRow %d col %d overhangs top row and must be '1'\n", r, c), 0);
				}
				if ((size_t)c >= row_len_safe(map->grid[r + 1])
					&& row_len_safe(map->grid[r]) > row_len_safe(map->grid[r + 1]))
				{
					if (map->grid[r][c] != '1')
						return (ft_printf("Error\nRow %d col %d overhangs bottom row and must be '1'\n", r, c), 0);
				}

				/*
				** For any non-leading whitespace: acceptable adjacent to ' ' are only '1' or ' '
				*/
				if (map->grid[r][c] == ' ' && c >= first_idx)
				{
					char	up = get_cell(map, r - 1, c);
					char	down = get_cell(map, r + 1, c);
					char	left = get_cell(map, r, c - 1);
					char	right = get_cell(map, r, c + 1);

					if ((up != '1' && up != ' ') || (down != '1' && down != ' ')
						|| (left != '1' && left != ' ') || (right != '1' && right != ' '))
						return (ft_printf("Error\nSpace at (%d,%d) adjacent to invalid cell\n", r, c), 0);
				}
			}
			c++;
		}
		r++;
	}
	return (1);
}

static int	check_boundaries(t_mapdata *map)
{
	// int	i;
	// int	j;

	// First validate the perimeter is all walls
	if (!validate_map_perimeter(map))
		return (0);
	
	// // Check internal walkable spaces are properly surrounded
	// i = 1;
	// while (i < map->height - 1)
	// {
	// 	j = 1;
	// 	while (j < map->width - 1)
	// 	{
	// 		if (is_walkable(map->grid[i][j]))
	// 		{
	// 			// Ensure adjacent cells are valid (walkable or wall, not invalid chars)
	// 			if (!is_valid_char(map->grid[i - 1][j]) ||
	// 				!is_valid_char(map->grid[i + 1][j]) ||
	// 				!is_valid_char(map->grid[i][j - 1]) ||
	// 				!is_valid_char(map->grid[i][j + 1]))
	// 			{
	// 				ft_printf("Error\nWalkable space at (%d,%d) adjacent to invalid cell\n", i, j);
	// 				return (0);
	// 			}
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (1);
}

// static int	flood_fill_check(t_mapdata *map, int x, int y, char **visited)
// {
// 	// If we reach the boundary, the map is not properly enclosed
// 	if (x < 0 || x >= map->height || y < 0 || y >= map->width)
// 	{
// 		ft_printf("Error\nPlayer can reach map boundary - map not enclosed\n");
// 		return (0);
// 	}
	
// 	// If already visited or hit a wall, stop recursion
// 	if (visited[x][y] == '1' || map->grid[x][y] == '1')
// 		return (1);
	
// 	// Mark as visited
// 	visited[x][y] = '1';
	
// 	// Continue flood fill in all 4 directions
// 	if (!flood_fill_check(map, x + 1, y, visited) ||
// 		!flood_fill_check(map, x - 1, y, visited) ||
// 		!flood_fill_check(map, x, y + 1, visited) ||
// 		!flood_fill_check(map, x, y - 1, visited))
// 		return (0);
	
// 	return (1);
// }

// static char	**create_visited_grid(t_mapdata *map)
// {
// 	char	**visited;
// 	int		i;
// 	int		j;

// 	visited = malloc(sizeof(char *) * map->height);
// 	if (!visited)
// 		return (NULL);
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		visited[i] = malloc(map->width + 1);
// 		if (!visited[i])
// 		{
// 			while (--i >= 0)
// 				free(visited[i]);
// 			free(visited);
// 			return (NULL);
// 		}
// 		j = 0;
// 		while (j < map->width)
// 			visited[i][j++] = '0';
// 		visited[i][map->width] = '\0';
// 		i++;
// 	}
// 	return (visited);
// }

// static void	free_visited_grid(char **visited, int height)
// {
// 	int	i;

// 	i = 0;
// 	while (i < height)
// 	{
// 		free(visited[i]);
// 		i++;
// 	}
// 	free(visited);
// }

// static int	validate_map_enclosure(t_mapdata *map)
// {
// 	char	**visited;
// 	int		result;

// 	visited = create_visited_grid(map);
// 	if (!visited)
// 		return (0);
// 	result = flood_fill_check(map, (int)map->player_y,
// 			(int)map->player_x, visited);
// 	if (!result)
// 		ft_printf("Error\nMap is not properly enclosed\n");
// 	free_visited_grid(visited, map->height);
// 	return (result);
// }

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
	// if (!validate_map_enclosure(map))
	// 	return (0);
	if (!validate_textures_exist(map))
		return (0);
	return (1);
}
