/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:59:15 by ataan             #+#    #+#             */
/*   Updated: 2026/01/23 21:45:54 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "cub3D by chicken et fam", false);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->pos_x = 3.0;
	g->pos_y = 10.0;
	g->dir_x = -1.0;
	g->dir_y = 0.0;
	g->plane_x = 0.0;
	g->plane_y = 0.66;
	if (!load_textures(g))
		return (0);
	g->north.width = g->north.img->width;
	g->north.height = g->north.img->height;
	g->south.width = g->south.img->width;
	g->south.height = g->south.img->height;
	g->east.width = g->east.img->width;
	g->east.height = g->east.img->height;
	g->west.width = g->west.img->width;
	g->west.height = g->west.img->height;
	return (1);
}

int	load_textures(t_game *g)
{
	g->north.img = mlx_load_png("textures/north.png");
	g->south.img = mlx_load_png("textures/south.png");
	g->east.img = mlx_load_png("textures/east.png");
	g->west.img = mlx_load_png("textures/west.png");
	if (!g->north.img || !g->south.img || !g->east.img || !g->west.img)
	{
		printf("Texture load failed");
		cleanup(g);
		return (0);
	}
	return (1);
}
