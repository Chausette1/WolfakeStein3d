#include "../../includes/include.h"

void generate_new_frame(t_mlxVar *data)
{
    generate_mini_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void move_player(t_mlxVar *data, int move)
{
    if (move == 1) // UP
    {
        data->player.y -= sin(data->player.fov_center) * STEP;
        data->player.x -= cos(data->player.fov_center) * STEP;
    }
    else if (move == 2) // DOWN
    {
        data->player.x += cos(data->player.fov_center) * STEP;
        data->player.y += sin(data->player.fov_center) * STEP;
    }
    else if (move == 3) // LEFT
    {
        data->player.fov_center -= data->player.rotation_angle;
        data->player.fov_center_x = data->player.x - cos(data->player.fov_center) * STEP;
        data->player.fov_center_y = data->player.y - sin(data->player.fov_center) * STEP;
    }
    else if (move == 4) // RIGHT
    {
        data->player.fov_center += data->player.rotation_angle;
        data->player.fov_center_x = data->player.x + cos(data->player.fov_center) * STEP;
        data->player.fov_center_y = data->player.y + sin(data->player.fov_center) * STEP;
    }
    generate_new_frame(data);
}

int key_hook(int keyCode, t_mlxVar *data)
{
    enum eKeycodes key = keyCode;
    if (key == KEY_ESC)
    {
        clean_end(data);
    }
    else if (key == KEY_Z || key == KEY_UP)
    {
        move_player(data, 1);
    }
    else if (key == KEY_Q || key == KEY_LEFT)
    {
        move_player(data, 3);
    }
    else if (key == KEY_S || key == KEY_DOWN)
    {
        move_player(data, 2);
    }
    else if (key == KEY_D || key == KEY_RIGHT)
    {
        move_player(data, 4);
    }
    else if (key == KEY_TAB)
    {
        if (data->is_mini_map)
            data->is_mini_map = false;
        else
            data->is_mini_map = true;
        printf("is_mini_map: %d\n", data->is_mini_map);
    }
    return 0;
}