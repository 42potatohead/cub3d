/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:16:00 by zabu-bak         #+#    #+#             */
/*   Updated: 2026/01/26 17:16:00 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*extract_texture_path(char *line)
{
	char	*trimmed;
	char	*path;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
		i += 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	trimmed = ft_strtrim(&line[i], " \t\n");
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		if (trimmed)
			free(trimmed);
		return (NULL);
	}
	path = ft_strdup(trimmed);
	free(trimmed);
	return (path);
}

static int	parse_rgb_color(char *color_str, int *color)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2]
		|| rgb_parts[3])
	{
		if (rgb_parts)
		{
			int i = 0;
			while (rgb_parts[i])
				free(rgb_parts[i++]);
			free(rgb_parts);
		}
		return (0);
	}
	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	int i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

static int	parse_color_line(t_mapdata *map, char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	trimmed = ft_strtrim(&line[i], " \t\n");
	if (!trimmed)
		return (0);
	if (line[0] == 'F' || (line[0] == ' ' && ft_strchr(line, 'F')))
	{
		if (!parse_rgb_color(trimmed, &map->floor_color))
		{
			free(trimmed);
			return (0);
		}
	}
	else if (line[0] == 'C' || (line[0] == ' ' && ft_strchr(line, 'C')))
	{
		if (!parse_rgb_color(trimmed, &map->ceiling_color))
		{
			free(trimmed);
			return (0);
		}
	}
	free(trimmed);
	return (1);
}

static int	parse_texture_line(t_mapdata *map, char *line)
{
	char	*path;

	if (ft_strncmp(line, "NO", 2) == 0 || 
		(line[0] == ' ' && ft_strnstr(line, "NO", ft_strlen(line))))
	{
		if (map->north_texture)
			return (0);
		path = extract_texture_path(line);
		if (!path)
			return (0);
		map->north_texture = path;
	}
	else if (ft_strncmp(line, "SO", 2) == 0 ||
		(line[0] == ' ' && ft_strnstr(line, "SO", ft_strlen(line))))
	{
		if (map->south_texture)
			return (0);
		path = extract_texture_path(line);
		if (!path)
			return (0);
		map->south_texture = path;
	}
	else if (ft_strncmp(line, "WE", 2) == 0 ||
		(line[0] == ' ' && ft_strnstr(line, "WE", ft_strlen(line))))
	{
		if (map->west_texture)
			return (0);
		path = extract_texture_path(line);
		if (!path)
			return (0);
		map->west_texture = path;
	}
	else if (ft_strncmp(line, "EA", 2) == 0 ||
		(line[0] == ' ' && ft_strnstr(line, "EA", ft_strlen(line))))
	{
		if (map->east_texture)
			return (0);
		path = extract_texture_path(line);
		if (!path)
			return (0);
		map->east_texture = path;
	}
	return (1);
}

int	parse_elements(t_mapdata *map, char *filename)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCannot open file: %s\n", filename);
		return (0);
	}
	result = 1;
	while ((line = get_next_line(fd)) && result)
	{
		if (line[0] == '\n' || (line[0] == ' ' && ft_strlen(ft_strtrim(line, " \t\n")) == 0))
		{
			free(line);
			continue;
		}
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			break;
		if (ft_strchr(line, 'N') && ft_strchr(line, 'O'))
			result = parse_texture_line(map, line);
		else if (ft_strchr(line, 'S') && ft_strchr(line, 'O'))
			result = parse_texture_line(map, line);
		else if (ft_strchr(line, 'W') && ft_strchr(line, 'E'))
			result = parse_texture_line(map, line);
		else if (ft_strchr(line, 'E') && ft_strchr(line, 'A'))
			result = parse_texture_line(map, line);
		else if (ft_strchr(line, 'F') || ft_strchr(line, 'C'))
			result = parse_color_line(map, line);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	return (result);
}