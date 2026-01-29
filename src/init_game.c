/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:59:15 by ataan             #+#    #+#             */
/*   Updated: 2026/01/29 16:04:31 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_game(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "cub3D by chicken et fam", false);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	set_player(g);
	if (!load_textures(g))
		return (0);
	return (1);
}

void	set_player(t_game *g)
{
	g->pos_x = g->map->player_x + 0.5;
	g->pos_y = g->map->player_y + 0.5;
	if (g->map->player_dir == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
	}
	else if (g->map->player_dir == 'S')
	{
		g->dir_x = 0;
		g->dir_y = 1;
	}
	else if (g->map->player_dir == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
	}
	else if (g->map->player_dir == 'W')
	{
		g->dir_x = -1;
		g->dir_y = 0;
	}
	g->plane_x = -g->dir_y * 0.66;
	g->plane_y = g->dir_x * 0.66;
}

int	load_textures(t_game *g)
{
	g->map->north.img = mlx_load_png(g->map->north_texture);
	g->map->south.img = mlx_load_png(g->map->south_texture);
	g->map->east.img = mlx_load_png(g->map->east_texture);
	g->map->west.img = mlx_load_png(g->map->west_texture);
	if (!g->map->north.img || !g->map->south.img || !g->map->east.img
		|| !g->map->west.img)
	{
		printf("Error\nTexture load failed\n");
		cleanup(g);
		return (0);
	}
	g->map->north.width = g->map->north.img->width;
	g->map->north.height = g->map->north.img->height;
	g->map->south.width = g->map->south.img->width;
	g->map->south.height = g->map->south.img->height;
	g->map->east.width = g->map->east.img->width;
	g->map->east.height = g->map->east.img->height;
	g->map->west.width = g->map->west.img->width;
	g->map->west.height = g->map->west.img->height;
	return (1);
}
