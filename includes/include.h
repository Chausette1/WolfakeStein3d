#ifndef WOLFAKASTEIN3D_H
#define WOLFAKASTEIN3D_H

#include "../MLX_LINUX/mlx.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH_WIN 900
#define LENGHT_WIN 1200
#define SQUARE_SIZE 60
#define STEP 10
#define PI 3.14159265358979323846

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

typedef struct s_mapType
{
    char **map;
    int length;
    int width;
} t_map;

typedef struct s_player
{
    double x;
    double y;
    double scale;
    double fov;
    double rotation_angle;
    double fov_center;
    double fov_center_x;
    double fov_center_y;
} t_player;

typedef struct s_mlxVar
{
    void *mlx;
    void *win;
    bool is_mini_map;
    t_img img;
    t_map map;
    t_player player;
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
int load_map(char *filename, t_map *map_struct);

/*
    key_hook functions
*/
int key_hook(int key, t_mlxVar *data);

/*
    image_generation functions
*/
void generate_frame(t_mlxVar *data);
void generate_mini_map(t_mlxVar *data);

/*
    math functions
*/
int **bresenham_algo(int x0, int y0, int x1, int y1);

#endif