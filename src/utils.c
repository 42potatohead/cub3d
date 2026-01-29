/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:42:45 by ataan             #+#    #+#             */
/*   Updated: 2026/01/29 21:26:34 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cleanup(t_game *g)
{
	if (g->map->north.img)
		mlx_delete_texture(g->map->north.img);
	if (g->map->south.img)
		mlx_delete_texture(g->map->south.img);
	if (g->map->east.img)
		mlx_delete_texture(g->map->east.img);
	if (g->map->west.img)
		mlx_delete_texture(g->map->west.img);
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->mlx)
	{
		mlx_close_window(g->mlx);
		mlx_terminate(g->mlx);
	}
	free_mapdata(g->map);
}

void	clear_image(t_game *g)
{
	ft_memset(g->img->pixels, 0, g->img->width * g->img->height
		* sizeof(uint32_t));
}
