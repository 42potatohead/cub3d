/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:01:32 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 20:30:08 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

static void	get_row_bounds(char *row, int *first, int *last)
{
	int	len;

	len = (int)row_len_safe(row);
	*first = 0;
	while (*first < len && is_space(row[*first]))
		(*first)++;
	*last = (int)len - 1;
	while (*last >= 0 && is_space(row[*last]))
		(*last)--;
}

static int	check_border_row(t_mapdata *map, int r, int c, int first)
{
	if (c >= first && map->grid[r][c] != '1' && map->grid[r][c] != ' ')
		return (ft_printf("Error\nMap border row %d has invalid char\n", r), 0);
	return (1);
}

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
		return (ft_printf("Error\nnR%d C%d overhangs top row\n", r, c), 0);
	if ((size_t)c >= row_len_safe(map->grid[r + 1])
		&& row_len_safe(map->grid[r]) > row_len_safe(map->grid[r + 1])
		&& map->grid[r][c] != '1')
		return (ft_printf("Error\nR%d C%d overhangs bottom row\n", r, c), 0);
	return (1);
}

static int	check_inner_space(t_mapdata *map, int r, int c)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_cell(map, r - 1, c);
	down = get_cell(map, r + 1, c);
	left = get_cell(map, r, c - 1);
	right = get_cell(map, r, c + 1);
	if ((up != '1' && up != ' ')
		|| (down != '1' && down != ' ')
		|| (left != '1' && left != ' ')
		|| (right != '1' && right != ' '))
		return (ft_printf("Error\nrow %d Space adjacent invalid cell\n", r), 0);
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
	if (map->grid[r][c] == ' ' && c >= 0)
		return (check_inner_space(map, r, c));
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
