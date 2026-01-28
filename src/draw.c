/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:37:07 by ataan             #+#    #+#             */
/*   Updated: 2026/01/28 12:21:11 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ceiling(t_game *g, t_ray *r, int x)
{
	int			y;
	uint32_t	*pixels;

	y = 0;
	pixels = (uint32_t *)g->img->pixels;
	while (y < r->draw_start)
	{
		pixels[y * WIDTH + x] = g->map->ceiling_color;
		y++;
	}
}

void	draw_wall(t_game *g, t_ray *r, t_tex *tex, int x)
{
	int		tex_y;
	double	tex_pos;
	double	step;
	int		y;

	step = (double)tex->height / r->line_height;
	tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		((uint32_t *)g->img->pixels)[y * WIDTH
			+ x] = ((uint32_t *)tex->img->pixels)[tex_y * tex->width
			+ r->tex_x];
		y++;
	}
}

void	draw_floor(t_game *g, t_ray *r, int x)
{
	int			y;
	uint32_t	*pixels;

	y = r->draw_end + 1;
	pixels = (uint32_t *)g->img->pixels;
	while (y < HEIGHT)
	{
		pixels[y * WIDTH + x] = g->map->floor_color;
		y++;
	}
}

/* Actual drawing */
void	draw(t_game *g, t_ray *r, t_tex *tex, int x)
{
	draw_ceiling(g, r, x);
	draw_wall(g, r, tex, x);
	draw_floor(g, r, x);
}
