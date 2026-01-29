/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:01:32 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 21:44:28 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	row_len_safe(char *row)
{
	if (!row)
		return (0);
	return (ft_strlen(row));
}

void	get_row_bounds(char *row, int *first, int *last)
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

int	check_border_row(t_mapdata *map, int r, int c, int first)
{
	if (c >= first && map->grid[r][c] != '1' && map->grid[r][c] != ' ')
		return (ft_printf("Error\nMap border row %d has invalid char\n", r), 0);
	return (1);
}
