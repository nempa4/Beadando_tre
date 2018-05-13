#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <iostream>
#include <vector>
#include "graphics.hpp"
#include "widgets.hpp"

class Push_button : public Widget
{
protected:
    bool _focused;
    std::string _esemeny;
public:
    Push_button(int x, int y, int sx, int sy, std::string esemeny, int menu_tipus);
    virtual bool is_focused();
    virtual std::string erteke() {}
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void action()=0;
    void set_focus()
    {
        _focused = true;
    }
    void remove_focus()
    {
        _focused = false;
    }
    virtual bool focusable() const
    {
        return true;
    }
};

#endif // PUSH_BUTTON_H
