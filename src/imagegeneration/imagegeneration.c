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

void generate_mini_map(t_mlxVar *data)
{
    int x;
    int y;
    int x_win;
    int y_win;
    int max_x;
    int max_y;

    char **map;

    x = (data->player.x * SQUARE_SIZE) - LENGHT_WIN / 2; // centrer la minimap sur le joueurs
    y = (data->player.y * SQUARE_SIZE) - WIDTH_WIN / 2;
    x_win = 0;
    y_win = 0;
    max_x = x + LENGHT_WIN;
    max_y = y + WIDTH_WIN;

    map = data->map.map;

    while (y < max_y)
    {
        x = (data->player.x * SQUARE_SIZE) - LENGHT_WIN / 2;
        x_win = 0;
        int y_in_map = y / SQUARE_SIZE;
        while (x < max_x)
        {
            int x_in_map = x / SQUARE_SIZE;
            if ((y_in_map < data->map.length) && (x_in_map < data->map.width))
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
            x++;
            x_win++;
        }
        y++;
        y_win++;
    }
}
