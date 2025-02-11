#include "../../includes/include.h"

void generate_new_frame(t_mlxVar *data)
{
    generate_mini_map(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
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
        for (int i = 0; i < data->map.length; i++)
        {
            for (int j = 0; j < data->map.width; j++)
            {
                if (data->map.map[i][j] == 'P')
                {
                    if (i - 1 >= 0)
                    {
                        printf("possition joueur update\n");
                        data->map.map[i - 1][j] = 'P';
                        data->map.map[i][j] = '0';
                        data->player.y = i - 1;
                        printf("New player coordinates: x = %d, y = %d\n", (int)data->player.x, (int)data->player.y);
                        generate_new_frame(data);
                        return 0;
                    }
                }
            }
        }
    }
    else if (key == KEY_Q || key == KEY_LEFT)
    {
        for (int i = 0; i < data->map.length; i++)
        {
            for (int j = 0; j < data->map.width; j++)
            {
                if (data->map.map[i][j] == 'P')
                {
                    if (j - 1 >= 0)
                    {
                        printf("possition joueur update\n");
                        data->map.map[i][j - 1] = 'P';
                        data->map.map[i][j] = '0';
                        data->player.x = j - 1;
                        printf("New player coordinates: x = %d, y = %d\n", (int)data->player.x, (int)data->player.y);
                        generate_new_frame(data);
                        return 0;
                    }
                }
            }
        }
    }
    else if (key == KEY_S || key == KEY_DOWN)
    {
        for (int i = 0; i < data->map.length; i++)
        {
            for (int j = 0; j < data->map.width; j++)
            {
                if (data->map.map[i][j] == 'P')
                {
                    if (i + 1 < data->map.length)
                    {
                        printf("possition joueur update\n");
                        data->map.map[i + 1][j] = 'P';
                        data->map.map[i][j] = '0';
                        data->player.y = i + 1;
                        printf("New player coordinates: x = %d, y = %d\n", (int)data->player.x, (int)data->player.y);
                        generate_new_frame(data);
                        return 0;
                    }
                }
            }
        }
    }
    else if (key == KEY_D || key == KEY_RIGHT)
    {
        for (int i = 0; i < data->map.length; i++)
        {
            for (int j = 0; j < data->map.width; j++)
            {
                if (data->map.map[i][j] == 'P')
                {
                    if (j + 1 < data->map.width)
                    {
                        printf("possition joueur update\n");
                        data->map.map[i][j + 1] = 'P';
                        data->map.map[i][j] = '0';
                        data->player.x = j + 1;
                        printf("New player coordinates: x = %d, y = %d\n", (int)data->player.x, (int)data->player.y);
                        generate_new_frame(data);
                        return 0;
                    }
                }
            }
        }
    }
    else if (key == KEY_TAB)
    {
        (void)key;
    }
    return 0;
}