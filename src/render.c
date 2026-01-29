/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:46:58 by ataan             #+#    #+#             */
/*   Updated: 2026/01/29 13:46:30 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render(t_game *g)
{
	t_tex	*tex;
	t_ray	ray;
	int		x;

	clear_image(g);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(g, &ray, x);
		init_dda(g, &ray);
		run_dda(g, &ray);
		compute_wall(g, &ray);
		tex = select_wall_texture(g, &ray);
		compute_tex_x(&ray, tex);
		draw(g, &ray, tex, x);
		x++;
	}
}

t_tex	*select_wall_texture(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (&g->map->west);
		else
			return (&g->map->east);
	}
	else
	{
		if (r->ray_dir_y > 0)
			return (&g->map->north);
		else
			return (&g->map->south);
	}
}

void	compute_tex_x(t_ray *r, t_tex *tex)
{
	r->tex_x = (int)(r->wall_x * tex->width);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = tex->width - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = tex->width - r->tex_x - 1;
}

/* Projection math
	compute perpendicular wall distance
	clamp distance
	compute line height
	compute draw start & end
	clamp to screen
*/
void	compute_wall(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->pos_x + (1 - r->step_x) / 2)
			/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->pos_y + (1 - r->step_y) / 2)
			/ r->ray_dir_y;
	if (r->perp_wall_dist < 0.1)
		r->perp_wall_dist = 0.1;
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = g->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = g->pos_x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
}
