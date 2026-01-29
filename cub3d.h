/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <zabu-bak@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:11:49 by ataan             #+#    #+#             */
/*   Updated: 2026/01/29 19:15:54 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600

# define COLLISION_BUFFER 0.2
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
	char			**grid;
	int				width;
	int				height;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	t_tex			north;
	t_tex			south;
	t_tex			east;
	t_tex			west;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	double			player_x;
	double			player_y;
	char			player_dir;
}					t_mapdata;

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
void				run_dda(t_game *g, t_ray *ray);
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
int					ft_check_av(int ac, char **av, int fd);

/* map parsing functions */
t_mapdata			*map_parser(char *filename);
void				free_mapdata(t_mapdata *map);
int					validate_map(t_mapdata *map);
int					parse_elements(t_mapdata *map, char *filename);
int					parse_map_grid(t_mapdata *map, char *filename);
int					parse_texture_line(t_mapdata *map, char *line);
int					parse_east_texture(t_mapdata *map, char *line);
int					parse_west_texture(t_mapdata *map, char *line);
int					parse_south_texture(t_mapdata *map, char *line);
int					parse_north_texture(t_mapdata *map, char *line);

void				free_split(char **split);
char				*extract_texture_path(char *line);
int					read_next_line(int fd, char **line);

int					calculate_max_width(char *filename);
int					update_max_width(int max_width, char *line);
int					parse_color_line(t_mapdata *map, char *line);
int					parse_rgb_color(char *color_str, uint32_t *color);

int					handle_map_line(t_mapdata *map, char *line, int *row,
						int *map_started);

char				*process_map_line(char *line, int target_width);

int					check_boundaries(t_mapdata *map);
int					is_space(char c);
int					check_middle_row(t_mapdata *map, int r, int c, int last);

size_t				row_len_safe(char *row);
void				get_row_bounds(char *row, int *first, int *last);
int					check_border_row(t_mapdata *map, int r, int c, int first);

#endif