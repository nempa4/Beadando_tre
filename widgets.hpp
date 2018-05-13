#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED
#include <iostream>
#include "graphics.hpp"

class Widget
{
protected:
    int _x, _y, _size_x, _size_y;



public:
    bool _checked;
    bool _striped;
    int sorszam, x_win, y_win, _menu_tipus;
    Widget(int x, int y, int sx, int sy, int menu_tipus);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() const = 0;
    virtual std::string erteke() = 0;
    virtual int menutipus()
    {
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
};

#endif // WIDGETS_HPP_INCLUDED
