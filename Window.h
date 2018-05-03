#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include "graphics.hpp"
#include "widgets.hpp"


class Window {
public:

protected:
    int _X, _Y;


public:
	std::vector<Widget*> widgets;
    Window(int X, int Y) ;
    void event_loop() ;
};

#endif // WINDOW_H
