#ifndef WOLFAKASTEIN3D_H
#define WOLFAKASTEIN3D_H

#include "../MLX_LINUX/mlx.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>

#define WIDTH_WIN 500
#define HEIHGT_WIN 500
#define SQUARE_SIZE 100
#define SQUARE_SPEED 10
#define X_START 200
#define Y_START 200

enum eKeycodes
{
    KEY_ESC = XK_Escape,
    KEY_Z = XK_z,
    KEY_Q = XK_q,
    KEY_S = XK_s,
    KEY_D = XK_d,
    KEY_UP = XK_Up,
    KEY_LEFT = XK_Left,
    KEY_DOWN = XK_Down,
    KEY_RIGHT = XK_Right,
    KEY_TAB = XK_Tab,
};

typedef struct s_img
{
    void *img_ptr;      // image identifier
    char *addr;         // address of the first pixel of the image
    int bits_per_pixel; // number of bits needed to represent a pixel color (32)
    int line_length;    // number of bytes used to store one line of the image in memory
    int endian;
} t_img;

typedef struct s_mlxVar
{
    void *mlx;
    void *win;
    t_img img;
} t_mlxVar;

/*
    init functions
*/
void init_game(t_mlxVar *data);

/*
    cleaning functions
*/
int clean_end(t_mlxVar *data);

/*
    file_reading functions
*/

/*
    key_hook functions
*/
int key_hook(int key, t_mlxVar *data);

#endif