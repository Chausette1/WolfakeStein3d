#include "../../includes/include.h"

void generate_player(t_mlxVar *data)
{
    int x;
    int y;

    x = 0;
    y = 0;

    data->player.fov = (PI / 180) * 70; // 70 degrees
    data->player.scale = 0.4;
    data->player.rotation_angle = (PI / 18); // 10 degrees
    while (y < data->map.length)
    {
        while (x < data->map.width)
        {
            char buffer = data->map.map[y][x];
            if (buffer == 'N' || buffer == 'S' || buffer == 'E' || buffer == 'W')
            {
                data->player.x = x * SQUARE_SIZE + SQUARE_SIZE / 2;
                data->player.y = y * SQUARE_SIZE + SQUARE_SIZE / 2;
                switch (buffer)
                {
                case 'N':
                    data->player.fov_center = PI / 2;
                    data->player.fov_center_x = data->player.x - 10;
                    data->player.fov_center_y = data->player.y;
                    break;
                case 'S':
                    data->player.fov_center = 3 * PI / 2;
                    data->player.fov_center_x = data->player.x + 10;
                    data->player.fov_center_y = data->player.y;
                    break;
                case 'E':
                    data->player.fov_center = PI;
                    data->player.fov_center_x = data->player.x;
                    data->player.fov_center_y = data->player.y - 10;
                    break;
                case 'W':
                    data->player.fov_center = 0;
                    data->player.fov_center_x = data->player.x;
                    data->player.fov_center_y = data->player.y + 10;
                    break;
                }
                data->map.map[y][x] = '0';
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