#include "../..//includes/include.h"

int **dxdy(int x0, int y0, int x1, int y1)
{
    int delta_x;
    int delta_y;
    int yi;
    int d_factor;

    int **point_coordinates;
    int *x_coordonnate;
    int *y_coordonnate;

    delta_x = x1 - x0;
    delta_y = y1 - y0;
    yi = 1;

    point_coordinates = malloc(2 * sizeof(int *)); // allocate memory for the points
    if (!point_coordinates)
        return NULL; // Échec de l'allocation

    x_coordonnate = malloc((abs(delta_x) + 1) * sizeof(int));
    y_coordonnate = malloc((abs(delta_x) + 1) * sizeof(int));

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

    if (delta_x < 0)
    {
        yi = -1;
        delta_y = -delta_y;
    }

    d_factor = 2 * delta_y - delta_x; // init the first d factor
    x_coordonnate[0] = x0;            // set the values of the first point of x
    y_coordonnate[0] = y0;            // set the values of the first point of x

    for (int i = 1; i < delta_x; i++)
    {
        x_coordonnate[i] = i + x0;
        if (d_factor > 0)
        {
            y_coordonnate[i] = y_coordonnate[i - 1] + yi;
            d_factor = d_factor + 2 * (delta_y - delta_x);
        }
        else
        {
            y_coordonnate[i] = y_coordonnate[i - 1];
            d_factor = d_factor + 2 * delta_y;
        }
    }
    return (point_coordinates);
}

int **dydx(int x0, int y0, int x1, int y1)
{
    int delta_x;
    int delta_y;
    int xi;
    int d_factor;

    int **point_coordinates;
    int *x_coordonnate;
    int *y_coordonnate;

    delta_x = x1 - x0;
    delta_y = y1 - y0;
    xi = 1;

    point_coordinates = malloc(2 * sizeof(int *)); // allocate memory for the points
    if (!point_coordinates)
        return NULL; // Échec de l'allocation
    x_coordonnate = malloc((abs(delta_y) + 1) * sizeof(int));
    y_coordonnate = malloc((abs(delta_y) + 1) * sizeof(int));
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

    if (delta_y < 0)
    {
        xi = -1;
        delta_x = -delta_x;
    }

    d_factor = 2 * delta_x - delta_y; // init the first d factor
    x_coordonnate[0] = x0;            // set the values of the first point of x
    y_coordonnate[0] = y0;            // set the values of the first point of y

    for (int i = 1; i < delta_y; i++)
    {
        y_coordonnate[i] = i + y0;
        if (d_factor > 0)
        {
            x_coordonnate[i] = x_coordonnate[i - 1] + xi;
            d_factor = d_factor + 2 * (delta_x - delta_y);
        }
        else
        {
            x_coordonnate[i] = x_coordonnate[i - 1];
            d_factor = d_factor + 2 * delta_x;
        }
    }
    return (point_coordinates);
}

int **bresenham_algo(int x0, int y0, int x1, int y1)
{
    int **point_coordinates;

    point_coordinates = malloc(2 * sizeof(int *));

    if (!point_coordinates)
    {
        return NULL;
    }

    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            point_coordinates = dxdy(x1, y1, x0, y0);
        }
        else
        {
            point_coordinates = dxdy(x0, y0, x1, y1);
        }
    }
    else
    {
        if (y0 > y1)
        {
            point_coordinates = dxdy(y1, x1, y0, x0);
        }
        else
        {
            point_coordinates = dxdy(y0, x0, y1, x1);
        }
    }

    return (point_coordinates);
}
