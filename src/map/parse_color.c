/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:39:52 by ataan             #+#    #+#             */
/*   Updated: 2026/01/30 03:38:55 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
	MLX42 expects ABGR format: (A << 24) | (B << 16) | (G << 8) | R
*/
int	parse_rgb_color(char *color_str, uint32_t *color)
{
	char	**rgb_parts;
	int		rgb[3];
	int		i;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2]
		|| rgb_parts[3])
		return (free_split(rgb_parts), 0);
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(rgb_parts[i]);
	free_split(rgb_parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
		return (0);
	*color = (0xFF << 24) | (rgb[2] << 16) | (rgb[1] << 8) | rgb[0];
	return (1);
}

int	parse_color_line(t_mapdata *map, char *line)
{
	char		*trimmed;
	int			i;
	uint32_t	color_value;

	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	trimmed = ft_strtrim(&line[i], " \t\n");
	if (!trimmed || !parse_rgb_color(trimmed, &color_value))
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	free(trimmed);
	if (line[0] == 'F')
	{
		if (map->floor_color != 256)
			return (0);
		map->floor_color = color_value;
	}
	else if (line[0] == 'C')
	{
		if (map->ceiling_color != 256)
			return (0);
		map->ceiling_color = color_value;
	}
	else
		return (0);
	return (1);
}
