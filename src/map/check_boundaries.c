/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:01:32 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 21:40:32 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_row_walls(t_mapdata *map, int r, int first, int last)
{
	if (last >= first)
	{
		if (map->grid[r][first] != '1')
			return (ft_printf("Error\nRow %d must start with wall\n", r), 0);
		if (map->grid[r][last] != '1')
			return (ft_printf("Error\nRow %d must end with wall\n", r), 0);
	}
	return (1);
}

static int	check_row_overhangs(t_mapdata *map, int r, int c)
{
	if ((size_t)c >= row_len_safe(map->grid[r - 1])
		&& row_len_safe(map->grid[r]) > row_len_safe(map->grid[r - 1])
		&& map->grid[r][c] != '1')
		return (ft_printf("Error\nR%d C%d overhangs top row\n", r, c), 0);
	if ((size_t)c >= row_len_safe(map->grid[r + 1])
		&& row_len_safe(map->grid[r]) > row_len_safe(map->grid[r + 1])
		&& map->grid[r][c] != '1')
		return (ft_printf("Error\nR%d C%d overhangs bottom row\n", r, c), 0);
	return (1);
}

int	check_row_boundaries(t_mapdata *map, int r)
{
	int	c;
	int	first;
	int	last;

	get_row_bounds(map->grid[r], &first, &last);
	c = 0;
	while ((size_t)c < row_len_safe(map->grid[r]))
	{
		if (r == 0 || r == map->height - 1)
			if (!check_border_row(map, r, c, first))
				return (0);
		if (r > 0 && r < map->height - 1)
			if (!check_middle_row(map, r, c, last))
				return (0);
		c++;
	}
	return (1);
}

int	check_middle_row(t_mapdata *map, int r, int c, int last)
{
	if (!check_row_walls(map, r, 0, last))
		return (0);
	if (!check_row_overhangs(map, r, c))
		return (0);
	return (1);
}

int	check_boundaries(t_mapdata *map)
{
	int	r;

	r = 0;
	while (r < map->height)
	{
		if (!map->grid[r])
			return (ft_printf("Error\nNull row at %d\n", r), 0);
		if (!check_row_boundaries(map, r))
			return (0);
		r++;
	}
	return (1);
}
