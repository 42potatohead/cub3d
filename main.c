/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:38:01 by ataan             #+#    #+#             */
/*   Updated: 2026/01/23 21:32:18 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*g;
	double	move;

	g = param;
	move = 0.1;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(g->mlx);
		return ;
	}
	if (key.key == MLX_KEY_W)
		move_forward(g, move);
	if (key.key == MLX_KEY_S)
		move_backward(g, move);
	if (key.key == MLX_KEY_D)
		move_right(g, move);
	if (key.key == MLX_KEY_A)
		move_left(g, move);
	if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_LEFT)
		look_left_right(key, g);
	render(g);
}

void	close_hook(void *param)
{
	t_game	*g;

	g = param;
	mlx_close_window(g->mlx);
}

int	main(void)
{
	t_game	g;

	if (!init_game(&g))
		return (-1);
	mlx_image_to_window(g.mlx, g.img, 0, 0);
	render(&g);
	mlx_key_hook(g.mlx, key_hook, &g);
	mlx_close_hook(g.mlx, close_hook, &g);
	mlx_loop(g.mlx);
	cleanup(&g);
	return (0);
}
