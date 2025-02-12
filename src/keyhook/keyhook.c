#include "../../includes/include.h"

void generate_new_frame(t_mlxVar *data)
{
    generate_mini_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void move_player(t_mlxVar *data, int x, int y)
{
    if (data->map.map[(int)data->player.y + y][(int)data->player.x + x] != '1')
    {
        data->map.map[(int)data->player.y + y][(int)data->player.x + x] = 'P';
        data->map.map[(int)data->player.y][(int)data->player.x] = '0';
        data->player.x += x;
        data->player.y += y;
        generate_new_frame(data);
    }
}

void move_minimap_vision(t_mlxVar *data, int move)
{
    for (int i = 0; i < data->map.length; i++)
    {
        for (int j = 0; j < data->map.width; j++)
        {
            if (data->map.map[i][j] == 'P')
            {
                switch (move)
                {
                case 1:
                    move_player(data, 0, -1); // UP
                    break;
                case 2:
                    move_player(data, -1, 0); // LEFT
                    break;
                case 3:
                    move_player(data, 0, 1); // DOWN
                    break;
                case 4:
                    move_player(data, 1, 0); // RIGHT
                    break;
                }
                return;
            }
        }
    }
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
        if (data->is_mini_map == true)
        {
            move_minimap_vision(data, 1);
        }
    }
    else if (key == KEY_Q || key == KEY_LEFT)
    {
        if (data->is_mini_map == true)
        {
            move_minimap_vision(data, 2);
        }
    }
    else if (key == KEY_S || key == KEY_DOWN)
    {
        if (data->is_mini_map == true)
        {
            move_minimap_vision(data, 3);
        }
    }
    else if (key == KEY_D || key == KEY_RIGHT)
    {
        if (data->is_mini_map == true)
        {
            move_minimap_vision(data, 4);
        }
    }
    else if (key == KEY_TAB)
    {
        (void)key;
    }
    return 0;
}