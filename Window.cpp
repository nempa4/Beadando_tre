#include "Window.h"
#include "graphics.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace genv;
using namespace std;

Window::Window(int X, int Y) :
    _X(X),_Y(Y)
{
    gout.open(X,Y);
}

void Window::event_loop()
{
	string hozzaadando;
    event ev;
    int focus = -1;
    while((gin >> ev) && (ev.keycode != key_escape))
    {
        if (ev.type == ev_mouse && (ev.button==btn_left || ev.button==btn_right))
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    widgets[i]->handle(ev);
                    if (widgets[i]->focusable())
                    {
                        widgets[i]->set_focus();
                    }
                }
                else
                {
                    if (widgets[i]->focusable())
                    {
                        widgets[i]->remove_focus();
                    }
                }
            }
        }

        for (Widget * w : widgets)
        {
            w->draw();
        }

        gout << color(255, 255, 255) << move_to(10, _Y-15) << text("Press 'Esc' to exit the program.") << refresh;
    }
}
