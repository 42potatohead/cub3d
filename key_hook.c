/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:38:52 by ataan             #+#    #+#             */
/*   Updated: 2026/01/27 13:47:24 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *g, double move)
{
	double	xbuffer;
	double	ybuffer;

	xbuffer = COLLISION_BUFFER;
	if (g->dir_x < 0)
		xbuffer *= -1;
	ybuffer = COLLISION_BUFFER;
	if (g->dir_y < 0)
		ybuffer *= -1;
	if (g->map->grid[(int)(g->pos_y)][(int)(g->pos_x + g->dir_x * move
			+ xbuffer)] == '0')
		g->pos_x += g->dir_x * move;
	if (g->map->grid[(int)(g->pos_y + g->dir_y * move
			+ ybuffer)][(int)(g->pos_x)] == '0')
		g->pos_y += g->dir_y * move;
}

void	move_backward(t_game *g, double move)
{
	double	xbuffer;
	double	ybuffer;

	xbuffer = COLLISION_BUFFER;
	if (g->dir_x > 0)
		xbuffer *= -1;
	ybuffer = COLLISION_BUFFER;
	if (g->dir_y > 0)
		ybuffer *= -1;
	if (g->map->grid[(int)(g->pos_y)][(int)(g->pos_x - g->dir_x * move
			+ xbuffer)] == '0')
		g->pos_x -= g->dir_x * move;
	if (g->map->grid[(int)(g->pos_y - g->dir_y * move
			+ ybuffer)][(int)(g->pos_x)] == '0')
		g->pos_y -= g->dir_y * move;
}

void	move_right(t_game *g, double move)
{
	double	xbuffer;
	double	ybuffer;

	xbuffer = COLLISION_BUFFER;
	if (g->dir_x > 0)
		xbuffer *= -1;
	ybuffer = COLLISION_BUFFER;
	if (g->dir_y < 0)
		ybuffer *= -1;
	if (g->map->grid[(int)(g->pos_y)][(int)(g->pos_x + g->dir_y * move
			+ ybuffer)] == '0')
		g->pos_x += g->dir_y * move;
	if (g->map->grid[(int)(g->pos_y - g->dir_x * move
			+ xbuffer)][(int)(g->pos_x)] == '0')
		g->pos_y -= g->dir_x * move;
}

void	move_left(t_game *g, double move)
{
	double	xbuffer;
	double	ybuffer;

	xbuffer = COLLISION_BUFFER;
	if (g->dir_x < 0)
		xbuffer *= -1;
	ybuffer = COLLISION_BUFFER;
	if (g->dir_y > 0)
		ybuffer *= -1;
	if (g->map->grid[(int)(g->pos_y)][(int)(g->pos_x - g->dir_y * move
			+ ybuffer)] == '0')
		g->pos_x -= g->dir_y * move;
	if (g->map->grid[(int)(g->pos_y + g->dir_x * move
			+ xbuffer)][(int)(g->pos_x)] == '0')
		g->pos_y += g->dir_x * move;
}

void	look_left_right(mlx_key_data_t key, t_game *g)
{
	double	rot;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	rot = 0.05;
	if (key.key == MLX_KEY_RIGHT)
		angle = -rot;
	else
		angle = rot;
	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
	g->dir_y = old_dir_x * sin(angle) + g->dir_y * cos(angle);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(angle) - g->plane_y * sin(angle);
	g->plane_y = old_plane_x * sin(angle) + g->plane_y * cos(angle);
}
