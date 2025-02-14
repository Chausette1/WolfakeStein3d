#include "../../includes/include.h"

void generate_new_frame(t_mlxVar *data)
{
    mlx_clear_window(data->mlx, data->win);
    generate_mini_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void rotate_player(t_mlxVar *data)
{
    if (data->player.fov_center >= 0 && data->player.fov_center <= 2 * PI)
    {
        data->player.fov_center_y = data->player.y - ((10 * STEP) * sin(data->player.fov_center));
    }
    else
    {
        data->player.fov_center_y = data->player.y + ((10 * STEP) * sin(data->player.fov_center));
    }

    if (data->player.fov_center <= PI / 2 && data->player.fov_center >= -PI / 2)
    {
        data->player.fov_center_x = data->player.x + ((10 * STEP) * cos(data->player.fov_center));
    }
    else
    {
        data->player.fov_center_x = data->player.x - ((10 * STEP) * cos(data->player.fov_center));
    }
}

void move_player(t_mlxVar *data, int move)
{
    if (move == 1) // UP
    {
        data->player.y -= sin(data->player.fov_center) * STEP;
        data->player.x += cos(data->player.fov_center) * STEP;
        data->player.fov_center_x = data->player.x - cos(data->player.fov_center) * 10 * STEP;
        data->player.fov_center_y = data->player.y - sin(data->player.fov_center) * 10 * STEP;
    }
    else if (move == 2) // DOWN
    {
        data->player.x -= cos(data->player.fov_center) * STEP;
        data->player.y += sin(data->player.fov_center) * STEP;
        data->player.fov_center_x = data->player.x - cos(data->player.fov_center) * 10 * STEP;
        data->player.fov_center_y = data->player.y - sin(data->player.fov_center) * 10 * STEP;
    }
    else if (move == 3) // LEFT
    {
        data->player.fov_center = fmod((data->player.fov_center + data->player.rotation_angle), 2 * PI);
        rotate_player(data);
    }
    else if (move == 4) // RIGHT
    {
        if (data->player.fov_center - data->player.rotation_angle < 0)
        {
            data->player.fov_center = (2 * PI) + (data->player.fov_center - data->player.rotation_angle);
        }
        else
        {
            data->player.fov_center = data->player.fov_center - data->player.rotation_angle;
        }
        rotate_player(data);
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