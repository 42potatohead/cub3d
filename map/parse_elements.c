/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:58 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/27 18:26:59 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*extract_texture_path(char *line)
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
	int		rgb[3];
	int		i;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2] || rgb_parts[3])
		return (free_split(rgb_parts), 0);
	i = -1;
	while (++i < 3)
	{
		ft_printf("%s\n", rgb_parts[i]);
		rgb[i] = ft_atoi(rgb_parts[i]);
	}
	i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		return (0);
	// MLX42 expects RGBA format: (R << 24) | (G << 16) | (B << 8) | A
	*color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
	return (1);
}

static int	parse_color_line(t_mapdata *map, char *line)
{
	char	*trimmed;
	int		i;
	int		*color;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F')
		color = &map->floor_color;
	else if (line[i] == 'C')
		color = &map->ceiling_color;
	else
		return (0);
	i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	trimmed = ft_strtrim(&line[i], " \t\n");
	if (!trimmed || !parse_rgb_color(trimmed, color))
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}


int	parse_elements(t_mapdata *map, char *filename)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nCannot open file: %s\n", filename), 0);
	result = 1;
	while ((line = get_next_line(fd)) && result)
	{
		if (line[0] == '\n' || (line[0] == ' ' && ft_strlen(ft_strtrim(line, " \t\n")) == 0))
			;
		else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			break;
		else if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'W') || ft_strchr(line, 'E'))
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
