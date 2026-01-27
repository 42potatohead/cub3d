/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:44:40 by ataan             #+#    #+#             */
/*   Updated: 2026/01/27 13:48:11 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ray setup per column:
	compute cameraX
	compute rayDirX / rayDirY
	set starting map cell
	compute deltaDistX / deltaDistY
	--> No DDA yet.
*/
void	init_ray(t_game *g, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = g->dir_x + g->plane_x * ray->camera_x;
	ray->ray_dir_y = g->dir_y + g->plane_y * ray->camera_x;
	ray->map_x = (int)g->pos_x;
	ray->map_y = (int)g->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* DDA initialization:
	determine stepX / stepY
	compute initial sideDistX / sideDistY
	reset hit
	--> “Which direction does the ray step, and how far is the first grid edge?”
*/
void	init_dda(t_game *g, t_ray *ray)
{
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->pos_y) * ray->delta_dist_y;
	}
}

/* Grid traversal loop:
	step through the grid
	choose X or Y step each iteration
	stop when wall is hit
	store which side was hit
*/
void	run_dda(t_game *g, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (g->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
