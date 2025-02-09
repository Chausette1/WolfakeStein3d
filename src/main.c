#include "../includes/include.h"

int main()
{
    t_mlxVar *mlx_data;

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