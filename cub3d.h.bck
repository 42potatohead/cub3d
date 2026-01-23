#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

#define WALL 1
#define GROUND 0

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
    
    // Floor and ceiling colors (RGB)
    int     floor_color;     // Floor color in RGB format
    int     ceiling_color;   // Ceiling color in RGB format
    
    // Player starting position and orientation
    double  player_x;        // Player starting X coordinate
    double  player_y;        // Player starting Y coordinate
    char    player_dir;      // Player starting direction (N, S, E, W)
    
}   t_mapdata;

typedef struct s_mlxdata 
{
    mlx_t* mlx;

}   t_mlxdata;

// Argument validation
void	ft_check_av(int ac, char **av, int fd);

#endif
