#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED
#include <iostream>
#include "graphics.hpp"

class Widget
{
protected:
    int _x, _y, _size_x, _size_y;



public:
	//std::string irany;
	bool _checked;
    bool _striped;
	int sorszam, x_eddig, y_eddig, _menu_tipus;
    Widget(int x, int y, int sx, int sy, int menu_tipus);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() const = 0;
    virtual std::string erteke() = 0;
    virtual int menutipus() {
		return _menu_tipus;
    }
    virtual void handle(genv::event ev) = 0;
    virtual bool focusable() const
    {
        return false;
    }
    virtual void set_focus() {}
    virtual void remove_focus() {}
    virtual bool is_focused() {}
    virtual void remove_drop() {}
    virtual void pushback(std::string) {}
    virtual void _pushback(std::string) {}
    virtual void draw_selected(genv::event ev) {}
};

#endif // WIDGETS_HPP_INCLUDED
