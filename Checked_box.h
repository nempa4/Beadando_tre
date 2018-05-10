#ifndef CHECKED_BOX_H
#define CHECKED_BOX_H

#include "widgets.hpp"
#include "graphics.hpp"
#include "Window.h"
#include "My_Window.h"
#include <sstream>

class Checked_box : public Widget {
protected:
    bool _checked;
    bool _striped;
    bool _focused;
    My_Window *_myparent;
public:
	int sor;
	int oszlop;
	int sorszam;
    Checked_box(My_Window * parent, int x, int y, int sx, int sy, int menu_tipus);
    virtual void draw() const;
    virtual std::string erteke(){
    	std::stringstream ss;
    	ss << _menu_tipus;
		return ss.str();
    }
    virtual void handle(genv::event ev);
    virtual bool is_checked();
    virtual bool is_striped();
    virtual bool is_focused() ;
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

#endif // CHECKED_BOX_H
