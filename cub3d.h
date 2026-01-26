/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:11:49 by ataan             #+#    #+#             */
/*   Updated: 2026/01/26 17:49:30 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600

# define COLLISION_BUFFER 0.2

static const char	*map[] = {"111111111111111111111111111111111",
		"111111111000000000110000000000001",
		"111111111011000001110000000000001",
		"111111111001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"111101111111110111000000100011111",
		"111101111111110111010100100011111",
		"110000001101010111000000100011111",
		"100000000000000011000000100011111",
		"100000000000000011010100100011111",
		"11000001110101011111011110N011111",
		"111101111111010111011110100011111",
		"111111111111111111111111111111111"};
# define MAP_W 33
# define MAP_H 14
# define TEX_W 64
# define TEX_H 64

typedef struct s_tex
{
	mlx_texture_t	*img;
	int				width;
	int				height;
}					t_tex;

typedef struct s_mapdata
{
	/*
        '0' = Empty space (walkable)
        '1' = Wall
        'N', 'S', 'E', 'W' = Player starting position and direction
        ' ' = Void (outside map boundaries)
    */
    char    **grid;          // 2D array representing the map layout
    int     width;           // Map width (number of columns)
    int     height;          // Map height (number of rows)
    
    // Texture paths
    char    *north_texture;  // Path to north wall texture
    char    *south_texture;  // Path to south wall texture
    char    *west_texture;   // Path to west wall texture
    char    *east_texture;   // Path to east wall texture
    t_tex			north;
	t_tex			south;
	t_tex			east;
	t_tex			west;
    // Floor and ceiling colors (RGB)
    int     floor_color;     // Floor color in RGB format
    int     ceiling_color;   // Ceiling color in RGB format
    
    // Player starting position and orientation
    double  player_x;        // Player starting X coordinate
    double  player_y;        // Player starting Y coordinate
    char    player_dir;      // Player starting direction (N, S, E, W)
    
}   t_mapdata;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
}					t_ray;



typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_mapdata		*map;
}					t_game;

/* key_hook.c */
void				move_forward(t_game *g, double move);
void				move_backward(t_game *g, double move);
void				move_right(t_game *g, double move);
void				move_left(t_game *g, double move);
void				look_left_right(mlx_key_data_t key, t_game *g);

/* render.c dda.c */
void				render(t_game *g);
void				init_ray(t_game *g, t_ray *ray, int x);
void				init_dda(t_game *g, t_ray *ray);
void				run_dda(t_ray *ray);
t_tex				*select_wall_texture(t_game *g, t_ray *r);
void				compute_tex_x(t_ray *r, t_tex *tex);
void				compute_wall(t_game *g, t_ray *r);
void				draw(t_game *g, t_ray *r, t_tex *tex, int x);

/* utils.c*/
void				clear_image(t_game *g);
void				cleanup(t_game *g);

/* init_game.c */
int					init_game(t_game *g);
int					load_textures(t_game *g);
void				set_player(t_game *g);

/* draw.c */
void				draw_ceiling(t_game *g, t_ray *r, int x);
void				draw_wall(t_game *g, t_ray *r, t_tex *tex, int x);
void				draw_floor(t_game *g, t_ray *r, int x);
void				draw(t_game *g, t_ray *r, t_tex *tex, int x);

// input validation
void	ft_check_av(int ac, char **av, int fd);

/* map parsing functions */
t_mapdata			*map_parser(char *filename);
void				free_mapdata(t_mapdata *map);
int					validate_map(t_mapdata *map);
int					parse_elements(t_mapdata *map, char *filename);
int					parse_map_grid(t_mapdata *map, char *filename);

#endif