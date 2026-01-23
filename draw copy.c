/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:37:07 by ataan             #+#    #+#             */
/*   Updated: 2026/01/23 19:37:27 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *g, t_ray *r, int x)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
	{
		mlx_put_pixel(g->img, x, y, g->ceiling_color);
		y++;
	}
}

void	draw_wall(t_game *g, t_ray *r, t_tex *tex, int x)
{
	int			tex_y;
	double		tex_pos;
	uint32_t	color;
	double		step;
	int			y;
	int			pixel_index;
	uint8_t		*pixels;

	step = (double)tex->height / r->line_height;
	tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * step;
	y = r->draw_start;
	pixels = (uint8_t *)tex->img->pixels;
	while (y <= r->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		pixel_index = (tex_y * tex->width + r->tex_x) * 4;
		color = (pixels[pixel_index] << 24) | (pixels[pixel_index + 1] << 16) 
			| (pixels[pixel_index + 2] << 8) | pixels[pixel_index + 3];
		mlx_put_pixel(g->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_game *g, t_ray *r, int x)
{
	int	y;

	y = r->draw_end + 1;
	while (y < HEIGHT)
	{
		mlx_put_pixel(g->img, x, y, g->floor_color);
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
