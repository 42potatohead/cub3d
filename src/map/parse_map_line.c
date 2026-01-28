/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:32 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 13:09:41 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*process_map_line(char *line, int target_width)
{
	char		*processed;
	char		*trimmed;
	size_t		i;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (NULL);
	processed = malloc(target_width + 1);
	if (!processed)
		return (free(trimmed), NULL);
	i = 0;
	while (trimmed && i < ft_strlen(trimmed))
	{
		if (trimmed[i] == ' ')
			processed[i] = '1';
		else
			processed[i] = trimmed[i];
		i++;
	}
	while (i < (size_t)target_width)
		processed[i++] = '1';
	processed[target_width] = '\0';
	free(trimmed);
	return (processed);
}
