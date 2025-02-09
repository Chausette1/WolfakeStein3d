#include "../../includes/include.h"

void generateFrame(t_mlxVar *data)
{
    for (int y = 0; y < HEIHGT_WIN; y++)
    {
        for (int x = 0; x < WIDTH_WIN; x++)
        {
            (void)data;

            /*
            lot of work here
            */
        }
    }
}

void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));

    *((unsigned int *)(offset + img->addr)) = color;
}