#ifndef CUB3D_H
#define CUB3D_H

#include "../MLX_LINUX/mlx.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 500

enum e_keycodes
{
    KEY_ESC = 65307,
    KEY_Z = 122,
    KEY_Q = 113,
    KEY_S = 115,
    KEY_D = 100,
    KEY_UP = 65362,
    KEY_LEFT = 65361,
    KEY_DOWN = 65364,
    KEY_RIGHT = 65363,
    KEY_TAB = 65289,
};

typedef struct s_mlxVar
{
    void *mlx_connection;
    void *mlx_window;
} t_mlx;

#endif