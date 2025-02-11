#include "../../includes/include.h"

void freeMap(t_map *map)
{
    int i;

    i = 0;

    while (i < map->length)
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
}

void free_memory(t_mlxVar *data)
{
    if (data->map.map != NULL)
    {
        freeMap(&data->map);
    }
    if (data->mlx)
    {
        free(data->mlx);
    }
    if (data)
    {
        free(data);
    }
}

int clean_end(t_mlxVar *data)
{
    if (data->mlx && data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
    }
    free_memory(data);
    printf("Cleaning up and exiting\n");
    exit(0);
}
