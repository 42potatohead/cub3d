/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:42:45 by ataan             #+#    #+#             */
/*   Updated: 2026/01/23 19:43:11 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *g)
{
	if (g->north.img)
		mlx_delete_texture(g->north.img);
	if (g->south.img)
		mlx_delete_texture(g->south.img);
	if (g->east.img)
		mlx_delete_texture(g->east.img);
	if (g->west.img)
		mlx_delete_texture(g->west.img);
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->mlx)
	{
		mlx_close_window(g->mlx);
		mlx_terminate(g->mlx);
	}
}

void	clear_image(t_game *g)
{
	memset(g->img->pixels, 0, g->img->width * g->img->height
		* sizeof(uint32_t));
}
