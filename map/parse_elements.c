/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:04:58 by zabu-bak          #+#    #+#             */
/*   Updated: 2026/01/28 11:47:15 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
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
		|| ft_strncmp(&line[i], "WE", 2) == 0
		|| ft_strncmp(&line[i], "EA", 2) == 0)
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

/*
	MLX42 expects ABGR format: (A << 24) | (B << 16) | (G << 8) | R
*/
static int	parse_rgb_color(char *color_str, uint32_t *color)
{
	char	**rgb_parts;
	int		rgb[3];
	int		i;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1]
		|| !rgb_parts[2] || rgb_parts[3])
		return (free_split(rgb_parts), 0);
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(rgb_parts[i]);
	free_split(rgb_parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		return (0);
	*color = (0xFF << 24) | (rgb[2] << 16) | (rgb[1] << 8) | rgb[0];
	return (1);
}

static int	parse_color_line(t_mapdata *map, char *line)
{
	char		*trimmed;
	int			i;
	uint32_t	color_value;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	i++;
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
		map->floor_color = color_value;
	else if (line[0] == 'C')
		map->ceiling_color = color_value;
	else
		return (0);
	return (1);
}

static int	is_empty_line(char *line)
{
	char	*trimmed;
	int		empty;

	if (!line || line[0] == '\n')
		return (1);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	empty = (ft_strlen(trimmed) == 0);
	free(trimmed);
	return (empty);
}

static int	is_map_start(char c)
{
	return (c == '1' || c == '0' || c == ' ');
}

static int	handle_element_line(t_mapdata *map, char *line, int *result)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		return (*result = parse_texture_line(map, line), 1);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (*result = parse_color_line(map, line), 1);
	return (0);
}

int	parse_elements(t_mapdata *map, char *filename)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nCannot open file: %s\n", filename), 0);
	line = get_next_line(fd);
	result = 1;
	while (line && result)
	{
		if (!is_empty_line(line) && is_map_start(line[0]))
			break ;
		if (!is_empty_line(line))
			handle_element_line(map, line, &result);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (result);
}
