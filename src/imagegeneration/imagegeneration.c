#include "../../includes/include.h"

void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));

    *((unsigned int *)(offset + img->addr)) = color;
}

int color(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
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

void print_player_on_minimap(t_mlxVar *data, int x_win, int y_win)
{
    int distance_max;
    int x;
    int y;
    int x_max;
    int y_max;
    int left_side;

    distance_max = SQUARE_SIZE * data->player.scale / 2; // distance max from the player
    x = data->player.x - distance_max;                   // chose the up left corner of the area around the player
    y = data->player.y - distance_max;
    x_max = x + distance_max * 2; // chose the down right corner of the area around the player
    y_max = y + distance_max * 2;
    x_win = x_win - distance_max; // chose the up left corner of the area around the player in the window
    y_win = y_win - distance_max;
    left_side = x_win;

    while (y < y_max)
    {
        x_win = left_side;
        x = data->player.x - (SQUARE_SIZE * data->player.scale / 2);
        while (x < x_max)
        {
            double distance = sqrt(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));
            if (distance <= distance_max)
            {
                put_pixel_to_image(&data->img, x_win, y_win, color(0, 128, 128));
            }
            x++;
            x_win++;
        }
        y++;
        y_win++;
    }
}

void print_player_fov_center(t_mlxVar *data)
{
    /*
        algorihtm of segment drawing breseham
    */

    int x0;
    int y0;
    int x1;
    int y1;
    int **point_coordinates;

    x0 = (int)data->player.x;
    y0 = (int)data->player.y;
    x1 = (int)data->player.fov_center_x;
    y1 = (int)data->player.fov_center_y;
    point_coordinates = bresenham_algo(x0, y0, x1, y1);
    if (point_coordinates == NULL)
    {
        printf("bresenham_algo a retourné NULL\n");
        return; // Quitter la fonction sans libérer la mémoire
    }

    if (point_coordinates == NULL)
    {
        return;
    }

    if (abs(y1 - y0) < abs(x1 - x0))
    {
        for (int i = 0; i < abs(x1 - x0); i++)
        {
            // need to transform the coordonate
            int tmp_x = point_coordinates[0][i] - (LENGHT_WIN / 2);
            int tmp_y = point_coordinates[1][i] - (WIDTH_WIN / 2);
            printf("test foireux\n");
            printf("x: %d, y: %d\n", tmp_x, tmp_y);
            put_pixel_to_image(&data->img, tmp_x, tmp_y, color(0, 128, 128));
            /*
            non concluant, to be fix
            */
        }
    }
    else
    {
        for (int i = 0; i < abs(y1 - y0); i++)
        {
            // need to transform the coordonate
            int tmp_x = point_coordinates[0][i] - (LENGHT_WIN / 2);
            int tmp_y = point_coordinates[1][i] - (WIDTH_WIN / 2);
            printf("test foireux\n");
            printf("x: %d, y: %d\n", tmp_x, tmp_y);
            put_pixel_to_image(&data->img, tmp_x, tmp_y, color(0, 128, 128));
            /*
            non concluant, to be fix
            */
        }
    }

    printf("avant free\n");
    if (point_coordinates[0])
    {
        printf("free 1\n");
        free(point_coordinates[0]);
    }
    if (point_coordinates[1])
    {
        printf("free 2\n");
        free(point_coordinates[1]);
    }
    printf("free 3\n");
    free(point_coordinates);
    printf("apres free\n");

    return;
}

void generate_mini_map(t_mlxVar *data)
{
    /*
    need to be fix too
    */
    int x;
    int y;
    int x_win;
    int y_win;
    int max_x;
    int max_y;

    char **map;

    x = data->player.x - (LENGHT_WIN / 2); // chose the up left corner of the windows
    y = data->player.y - (WIDTH_WIN / 2);
    x_win = 0; // x and y in the window
    y_win = 0;
    max_x = x + LENGHT_WIN; // chose the down right corner of the windows
    max_y = y + WIDTH_WIN;

    map = data->map.map;

    mlx_clear_window(data->mlx, data->win);

    while (y < max_y)
    {
        x = data->player.x - (LENGHT_WIN / 2); // chose the left side of the windows
        x_win = 0;
        int y_in_map = y / SQUARE_SIZE;
        while (x < max_x)
        {
            int x_in_map = x / SQUARE_SIZE;
            if (is_coordonate_in_map(data, x_in_map, y_in_map) == 0) // if we're in the map
            {
                char buf = map[y_in_map][x_in_map]; // get the value of the map
                if (buf == '1')                     // if wall
                {
                    if (y % SQUARE_SIZE == 0 || x % SQUARE_SIZE == 0)
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, color(255, 255, 255));
                    }
                    else
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, color(255, 0, 0));
                    }
                }
                else
                {
                    if (y % SQUARE_SIZE == 0 || x % SQUARE_SIZE == 0)
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, color(255, 255, 255));
                    }
                    else
                    {
                        put_pixel_to_image(&data->img, x_win, y_win, color(0, 0, 0));
                    }
                }
            }
            else
            {
                put_pixel_to_image(&data->img, x_win, y_win, color(0, 0, 0));
            }
            x++;
            x_win++;
        }
        y++;
        y_win++;
    }
    print_player_on_minimap(data, LENGHT_WIN / 2, WIDTH_WIN / 2);
    print_player_fov_center(data);
}
