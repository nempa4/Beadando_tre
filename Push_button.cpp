#include "Push_button.h"
#include "graphics.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace genv;
using namespace std;

Push_button::Push_button(int x, int y, int sx, int sy, std::string esemeny, int menu_tipus) : Widget(x,y,sx,sy, menu_tipus)
{
    _esemeny = esemeny;
}

bool Push_button::is_focused()
{
    return _focused;
}

void Push_button::draw() const
{
    if (_focused)
    {
        if (_menu_tipus == 8)
        {
            gout << move_to(_x, _y) << color(20, 20, 230) << box(_size_x, _size_y);
            gout << move_to(_x+2, _y+2) << color(100, 100, 125) << box(_size_x-4, _size_y-4);
            gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2)+2, ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2+2) << color(0, 0, 0) << text(_esemeny);
            gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2), ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2) << color(215, 215, 255) << text(_esemeny);
        }
        else
        {
            gout << move_to(_x, _y) << color(230, 20, 20) << box(_size_x, _size_y);
            gout << move_to(_x+2, _y+2) << color(125, 100, 100) << box(_size_x-4, _size_y-4);
            gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2)+2, ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2+2) << color(0, 0, 0) << text(_esemeny);
            gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2), ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2) << color(255, 215, 215) << text(_esemeny);
        }
    }
    else
    {
        gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
        gout << move_to(_x+2, _y+2) << color(50, 50, 50) << box(_size_x-4, _size_y-4);
        gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2)+2, ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2+2) << color(0, 0, 0) << text(_esemeny);
        gout << move_to((_x+_size_x/2)-(gout.twidth(_esemeny)/2), ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2) << color(255, 255, 255) << text(_esemeny);
    }
}

void Push_button::handle(event ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y))
    {
        cout << "action" << endl;
        action();
    }
}
