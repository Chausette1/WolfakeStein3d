#include "../../includes/include.h"

void init_game(t_mlxVar *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        printf("Error\n");
        clean_end(data);
        exit(1);
    }
    data->win = mlx_new_window(data->mlx, WIDTH_WIN, HEIHGT_WIN, "Wolfakastein3D");
    if (!data->win)
    {
        printf("Error\n");
        clean_end(data);
        exit(1);
    }
    data->img.img_ptr = mlx_new_image(data->mlx, WIDTH_WIN, HEIHGT_WIN);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

    mlx_hook(data->win, 17, 0, clean_end, data);
    mlx_key_hook(data->win, key_hook, data);
}