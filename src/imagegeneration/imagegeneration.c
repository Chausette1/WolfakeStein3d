#include "../../includes/include.h"

void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));

    *((unsigned int *)(offset + img->addr)) = color;
}

void generate_frame(t_mlxVar *data)
{
    for (int y = 0; y < WIDTH_WIN; y++)
    {
        for (int x = 0; x < LENGHT_WIN; x++)
        {
            (void)data;

            /*
            lot of work here
            */
        }
    }
}

int is_coordonate_in_map(t_mlxVar *data, int x, int y)
{
    if ((y < data->map.length) && (x < data->map.width)) // check if the coordonate is in the map
    {
        if (x >= 0 && y >= 0) // check if the coordonate is in the map
        {
            return (0);
        }
    }
    return (1);
}

void generate_mini_map(t_mlxVar *data)
{
    int x;
    int y;
    int x_win;
    int y_win;
    int max_x;
    int max_y;

    char **map;

    for (int i = 0; i < data->map.length; i++)
    {
        for (int j = 0; j < data->map.width; j++)
        {
            printf("%c", data->map.map[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    x = (data->player.x * SQUARE_SIZE) - LENGHT_WIN / 2; // centrer la minimap sur le joueurs
    y = (data->player.y * SQUARE_SIZE) - WIDTH_WIN / 2;
    x_win = 0;
    y_win = 0;
    max_x = x + LENGHT_WIN;
    max_y = y + WIDTH_WIN;

    map = data->map.map;

    mlx_clear_window(data->mlx, data->win);

    while (y < max_y)
    {
        x = (data->player.x * SQUARE_SIZE) - LENGHT_WIN / 2;
        x_win = 0;
        int y_in_map = y / SQUARE_SIZE;
        while (x < max_x)
        {
            int x_in_map = x / SQUARE_SIZE;
            if (is_coordonate_in_map(data, x_in_map, y_in_map) == 0)
            {
                char buf = map[y_in_map][x_in_map];
                if (buf == '1')
                {
                    if (y % SQUARE_SIZE == 0 || x % SQUARE_SIZE == 0)
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, 0x00FFFFFF);
                    }
                    else
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, 0x00FF0000);
                    }
                }
                else if (buf == 'P')
                {
                    put_pixel_to_image(&data->img, x_win, y_win, 0x00FFFFFF);
                }
                else
                {
                    if (y % SQUARE_SIZE == 0 || x % SQUARE_SIZE == 0)
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, 0x00FFFFFF);
                    }
                    else
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, 0x00000000);
                    }
                }
            }
            else
            {
                put_pixel_to_image(&data->img, x_win, y_win, 0x00000000);
            }
            x++;
            x_win++;
        }
        y++;
        y_win++;
    }
}
