#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(int x, int y, int sx, int sy, int menu_tipus) : _x(x), _y(y), _size_x(sx), _size_y(sy), _menu_tipus(menu_tipus)
{
    x_win = false;
    y_win = false;
}

bool Widget::is_selected(int mouse_x, int mouse_y)
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}






