#include "../..//includes/include.h"

int **init_malloc(int size)
{
    int **point_coordinates;
    int *x_coordonnate;
    int *y_coordonnate;

    point_coordinates = malloc(2 * sizeof(int *)); // allocate memory for the points
    if (!point_coordinates)
        return NULL; // Échec de l'allocation

    x_coordonnate = malloc((size + 1) * sizeof(int));
    y_coordonnate = malloc((size + 1) * sizeof(int));
    if (!x_coordonnate || !y_coordonnate)
    {
        // En cas d'échec, libérer tout ce qui a été alloué
        if (x_coordonnate)
            free(x_coordonnate);
        if (y_coordonnate)
            free(y_coordonnate);
        free(point_coordinates);
        return NULL;
    }

    point_coordinates[0] = x_coordonnate;
    point_coordinates[1] = y_coordonnate;
    return point_coordinates;
}

int **dx(int x0, int y0, int x1, int y1)
{
    int delta_x;

    int **point_coordinates;

    delta_x = x1 - x0;

    (void)y1;

    point_coordinates = init_malloc(abs(delta_x));
    if (!point_coordinates)
    {
        return NULL;
    }

    if (delta_x < 0)
    {
        delta_x = -delta_x;
    }
    point_coordinates[0][0] = x0; // set the values of the first point of x
    point_coordinates[1][0] = y0; // set the values of the first point of y

    for (int i = 1; i < delta_x; i++)
    {
        point_coordinates[0][i] = i + x0;
        point_coordinates[1][i] = y0;
    }
    return (point_coordinates);
}

int **dy(int x0, int y0, int x1, int y1)
{
    int delta_y;

    int **point_coordinates;

    delta_y = y1 - y0;

    (void)x1;

    point_coordinates = init_malloc(abs(delta_y));
    if (!point_coordinates)
    {
        return NULL;
    }

    if (delta_y < 0)
    {
        delta_y = -delta_y;
    }
    point_coordinates[0][0] = x0; // set the values of the first point of x
    point_coordinates[1][0] = y0; // set the values of the first point of y

    for (int i = 1; i < delta_y; i++)
    {
        point_coordinates[0][i] = x0;
        point_coordinates[1][i] = i + y0;
    }
    return (point_coordinates);
}

int **dxdy(int x0, int y0, int x1, int y1)
{
    int delta_x;
    int delta_y;
    int yi;
    int d_factor;

    int **point_coordinates;

    delta_x = x1 - x0;
    delta_y = y1 - y0;
    yi = 1;

    point_coordinates = init_malloc(abs(delta_x));
    if (!point_coordinates)
    {
        return NULL;
    }

    if (delta_y < 0)
    {
        yi = -1;
        delta_y = -delta_y;
    }

    d_factor = (2 * delta_y) - delta_x; // init the first d factor
    point_coordinates[0][0] = x0;       // set the values of the first point of x
    point_coordinates[1][0] = y0;       // set the values of the first point of y
    printf("point 0 x : %d, y : %d\n", x0, y0);
    printf("point 1 x : %d, y : %d\n", x1, y1);
    for (int i = 1; i < abs(delta_x); i++)
    {
        point_coordinates[0][i] = i + x0;
        if (d_factor > 0)
        {
            point_coordinates[1][i] = point_coordinates[1][i - 1] + yi;
            d_factor = d_factor + (2 * (abs(delta_y) - abs(delta_x)));
        }
        else
        {
            point_coordinates[1][i] = point_coordinates[1][i - 1];
            d_factor = d_factor + (2 * abs(delta_y));
        }
        printf("d_factor : %d\n", d_factor);
    }

    printf("delta_x : %d\n", delta_x);
    printf("delta_y : %d\n", delta_y);
    return (point_coordinates);
}

int **dydx(int x0, int y0, int x1, int y1)
{
    int delta_x;
    int delta_y;
    int xi;
    int d_factor;

    int **point_coordinates;

    delta_x = x1 - x0;
    delta_y = y1 - y0;
    xi = 1;

    point_coordinates = init_malloc(abs(delta_y));
    if (!point_coordinates)
    {
        return NULL;
    }

    if (delta_x < 0)
    {
        xi = -1;
        delta_x = -delta_x;
    }

    d_factor = (2 * delta_x) - delta_y; // init the first d factor
    point_coordinates[0][0] = x0;       // set the values of the first point of x
    point_coordinates[1][0] = y0;       // set the values of the first point of y

    for (int i = 1; i < abs(delta_y); i++)
    {
        point_coordinates[1][i] = i + y0;
        if (d_factor > 0)
        {
            point_coordinates[0][i] = point_coordinates[0][i - 1] + xi;
            d_factor = d_factor + 2 * (abs(delta_x) - abs(delta_y));
        }
        else
        {
            point_coordinates[0][i] = point_coordinates[0][i - 1];
            d_factor = d_factor + 2 * abs(delta_x);
        }
    }
    return (point_coordinates);
}

int **bresenham_algo(int x0, int y0, int x1, int y1)
{

    if ((x0 == x1 || y0 == y1))
    {
        if (x0 == x1 && y0 == y1)
        {
            return NULL;
        }
        if (x0 == x1)
        {
            return dy(0, y0, 0, y1);
        }
        else
        {
            return dx(x0, 0, x1, 0);
        }
    }

    if (abs(y1 - y0) <= abs(x1 - x0))
    {
        return dxdy(x0, y0, x1, y1);
    }
    else
    {
        return dydx(x0, y0, x1, y1);
    }
}
