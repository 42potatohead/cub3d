/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:10:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 11:49:09 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_north_texture(t_mapdata *map, char *line)
{
	char	*path;

	if (map->north_texture)
		return (0);
	path = extract_texture_path(line);
	if (!path)
		return (0);
	map->north_texture = path;
	return (1);
}

int	parse_south_texture(t_mapdata *map, char *line)
{
	char	*path;

	if (map->south_texture)
		return (0);
	path = extract_texture_path(line);
	if (!path)
		return (0);
	map->south_texture = path;
	return (1);
}

int	parse_west_texture(t_mapdata *map, char *line)
{
	char	*path;

	if (map->west_texture)
		return (0);
	path = extract_texture_path(line);
	if (!path)
		return (0);
	map->west_texture = path;
	return (1);
}

int	parse_east_texture(t_mapdata *map, char *line)
{
	char	*path;

	if (map->east_texture)
		return (0);
	path = extract_texture_path(line);
	if (!path)
		return (0);
	map->east_texture = path;
	return (1);
}

int	parse_texture_line(t_mapdata *map, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0
		|| (line[0] == ' ' && ft_strnstr(line, "NO", ft_strlen(line))))
		return (parse_north_texture(map, line));
	else if (ft_strncmp(line, "SO", 2) == 0
		|| (line[0] == ' ' && ft_strnstr(line, "SO", ft_strlen(line))))
		return (parse_south_texture(map, line));
	else if (ft_strncmp(line, "WE", 2) == 0
		|| (line[0] == ' ' && ft_strnstr(line, "WE", ft_strlen(line))))
		return (parse_west_texture(map, line));
	else if (ft_strncmp(line, "EA", 2) == 0
		|| (line[0] == ' ' && ft_strnstr(line, "EA", ft_strlen(line))))
		return (parse_east_texture(map, line));
	return (1);
}
