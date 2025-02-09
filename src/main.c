#include "../includes/include.h"

int main(int argc, char **argv)
{
    t_mlxVar *mlx_data;

    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }

    mlx_data->map.map = load_map(argv[1]);

    mlx_data = malloc(sizeof(t_mlxVar));
    if (mlx_data == NULL)
    {
        printf("Error\n");
        return 1;
    }

    init_game(mlx_data);
    mlx_loop(mlx_data->mlx);
    return 0;
}