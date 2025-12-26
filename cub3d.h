#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

typedef struct s_mapdata
{
    //TODO: decide on map variables, initilize and declare;
}   t_mapdata;

typedef struct s_mlxdata 
{
    mlx_t* mlx;

}   t_mlxdata;

// Argument validation
void	ft_check_av(int ac, char **av, int fd);

#endif
