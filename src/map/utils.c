/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:38:40 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 12:57:15 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	update_max_width(int max_width, char *line)
{
	int	current_width;

	current_width = ft_strlen(line);
	if (current_width > 0 && line[current_width - 1] == '\n')
		current_width--;
	if (current_width > max_width)
		max_width = current_width;
	return (max_width);
}

int	calculate_max_width(char *filename)
{
	int		fd;
	char	*line;
	int		max_width;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	max_width = 0;
	map_started = 0;
	while (read_next_line(fd, &line))
	{
		if (!map_started)
			map_started = (line[0] == '1' || line[0] == '0' || line[0] == ' ');
		if (map_started)
			max_width = update_max_width(max_width, line);
		free(line);
	}
	return (close(fd), max_width);
}

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

int	read_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (0);
	return (1);
}
