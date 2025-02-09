#include "../../includes/include.h"

int key_hook(int keyCode, t_mlxVar *data)
{
    printf("Keycode: %d\n", keyCode);
    enum eKeycodes key = keyCode;
    if (key == KEY_ESC)
    {
        clean_end(data);
    }
    else if (key == KEY_Z || key == KEY_UP)
    {
        (void)key;
    }
    else if (key == KEY_Q || key == KEY_LEFT)
    {
        (void)key;
    }
    else if (key == KEY_S || key == KEY_DOWN)
    {
        (void)key;
    }
    else if (key == KEY_D || key == KEY_RIGHT)
    {
        (void)key;
    }
    else if (key == KEY_TAB)
    {
        (void)key;
    }
    return 0;
}