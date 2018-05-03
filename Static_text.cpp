#include "Static_text.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace genv;
using namespace std;

Static_text::Static_text(int x, int y, int sx, int sy, int menu_tipus, string felirat) : Widget(x,y,sx,sy, menu_tipus)
{
	_felirat = felirat;
}

void Static_text::draw() const
{
	gout << move_to(_x, _y) << color(95, 95, 95) << box(_size_x, _size_y);
	gout << move_to(_x+2, _y+2) << color(50, 50, 50) << box(_size_x-4, _size_y-4);
	gout << move_to(_x+7, ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2+2) << color(0, 0, 0) << text(_felirat);
	gout << move_to(_x+5, ((_y+_size_y/2))+gout.cascent()/2-gout.cdescent()/2) << color(255, 255, 255) << text(_felirat);
}

bool Static_text::is_focused()
{
    return _focused;
}
