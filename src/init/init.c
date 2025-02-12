#include "../../includes/include.h"

void generate_player(t_mlxVar *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < data->map.length)
    {
        while (x < data->map.width)
        {
            if (data->map.map[y][x] == 'N' || data->map.map[y][x] == 'S' || data->map.map[y][x] == 'E' || data->map.map[y][x] == 'W')
            {
                data->player.x = x;
                data->player.y = y;
                data->map.map[y][x] = 'P';
                return;
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void init_game(t_mlxVar *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        printf("Error\n");
        clean_end(data);
        exit(1);
    }
    data->win = mlx_new_window(data->mlx, LENGHT_WIN, WIDTH_WIN, "Wolfakastein3D");
    if (!data->win)
    {
        printf("Error\n");
        clean_end(data);
        exit(1);
    }
    data->img.img_ptr = mlx_new_image(data->mlx, LENGHT_WIN, WIDTH_WIN);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

    data->is_mini_map = true;
    generate_player(data);
    generate_mini_map(data);

    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);

    mlx_hook(data->win, 17, 0, clean_end, data);
    mlx_key_hook(data->win, key_hook, data);
}