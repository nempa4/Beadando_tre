#include "Checked_box.h"
#include "graphics.hpp"
#include <iostream>
using namespace genv;

Checked_box::Checked_box(My_Window * parent, int x, int y, int sx, int sy, int menu_tipus)
    : Widget(x,y,sx,sy,menu_tipus), _myparent(parent)
{
	_focused=false;
    _checked=false;
    _striped=false;

}

void Checked_box::draw() const
{
    gout << move_to(_x, _y) << color(200,200,200) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    if (_focused) {
		gout << move_to(_x, _y) << color(0,255,0) << box(_size_x, _size_y);
		gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    }
    if (_checked) {
        gout << color(255,0,0);
        gout << move_to(_x+_size_x/4, _y+_size_y/4) << line(_size_x-_size_x/2, _size_y-_size_y/2);
        gout << move_to(_x+_size_x/4+1, _y+_size_y/4) << line(_size_x-_size_y/2, _size_y-_size_y/2);
        gout << move_to(_x+_size_x-_size_x/4, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
        gout << move_to(_x+_size_x-_size_x/4-1, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
    }
    if (_striped) {
        gout << color(0,0,255);
        gout << move_to(_x+_size_x/4, _y+_size_y/4) << box(_size_x/2, _size_y/2);
        //gout << move_to(_x+_size_x/3, _y+4) << box(_size_x_size_x/3, _size_y-8);
    }
}

void Checked_box::handle(event ev)
{
    if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
		if (!_checked && !_striped) {
			_checked = true;
			std::cout << sorszam << std::endl;
			//std::cout << oszlop << std::endl;
		}
    }
    if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_right) {
		if (!_striped && !_checked) {
			_striped = true;
		}
    }

}
bool Checked_box::is_checked()
{
    return _checked;
}

bool Checked_box::is_striped()
{
    return _striped;
}

bool Checked_box::is_focused()
{
    return _focused;
}

