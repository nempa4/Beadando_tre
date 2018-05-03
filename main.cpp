#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "graphics.hpp"
#include "widgets.hpp"
#include "Choose_menu.h"
#include "beiros.h"
#include "Push_button.h"
#include "Static_text.h"
#include "Window.h"
//#include "Checked_box.h"

using namespace std;
using namespace genv;

class My_Window;

class Checked_box : public Widget
{
protected:
    bool _focused;
    My_Window *_myparent;
public:
    int sor;
    int oszlop;
    Checked_box(My_Window * parent, int x, int y, int sx, int sy, int menu_tipus)
        : Widget(x,y,sx,sy,menu_tipus), _myparent(parent)
    {
        _focused=false;
        _checked=false;
        _striped=false;

    }
    void draw() const
    {
        gout << move_to(_x, _y) << color(200,200,200) << box(_size_x, _size_y);
        gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
        if (_focused)
        {
            gout << move_to(_x, _y) << color(0,255,0) << box(_size_x, _size_y);
            gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
        }
        if (_checked)
        {
            gout << color(255,0,0);
            gout << move_to(_x+_size_x/4, _y+_size_y/4) << line(_size_x-_size_x/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x/4+1, _y+_size_y/4) << line(_size_x-_size_y/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x-_size_x/4, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x-_size_x/4-1, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
        }
        if (_striped)
        {
            gout << color(0,0,255);
            gout << move_to(_x+_size_x/4, _y+_size_y/4) << box(_size_x/2, _size_y/2);
            //gout << move_to(_x+_size_x/3, _y+4) << box(_size_x_size_x/3, _size_y-8);
        }
    }
    virtual void action();
    virtual void action2();
    std::string erteke()
    {
        std::stringstream ss;
        ss << _menu_tipus;
        return ss.str();
    }
    void handle(event ev)
    {
        if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left)
        {
            action();

            std::cout << sorszam << std::endl;
            std::cout << x_eddig << std::endl;
            std::cout << y_eddig << std::endl;
            //std::cout << irany << std::endl;
            if (!_checked && !_striped)
            {
                _checked = true;

                //std::cout << oszlop << std::endl;
            }
        }
        if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_right)
        {
        	action2();
            if (!_striped && !_checked)
            {
                _striped = true;
            }
        }

    }
    bool is_checked()
    {
        return _checked;
    }
    bool is_striped()
    {
        return _striped;
    }
    bool is_focused()
    {
        return _focused;
    }
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

class My_Window : public Window
{
public:
    My_Window(int X, int Y) : Window(X,Y)
    {
        _X = X;
        _Y = Y;
        for (unsigned int i = 0; i < 15; i++)
        {
            for (unsigned int j = 0; j < 15; j++)
            {
                Checked_box *ckb1;
                ckb1 = new Checked_box(this, 25+i*50, 45+j*50, 50, 50, 0);
                widgets.push_back(ckb1);
                if (j!=0)
                {
                    ckb1->sorszam = i*15+j;
                }
                else
                {
                    ckb1->sorszam = i*10+j;
                }
            }
        }
    }
    void x_gyozelem()
    {
        string str1 = "RED X - WINS";
        cout << "GYOZELEM" << endl;;
        widgets.clear();
        gout << move_to(0, 0) << color(0, 0, 0) << box(_X, _Y);
        gout << move_to(_X/2-gout.twidth(str1)/2, _Y/2) << color(255, 255, 255) << text(str1) << refresh;
    }
    void y_gyozelem()
    {
        string str2 = "BLUE BOX - WINS";
        cout << "B_GYOZELEM" << endl;;
        widgets.clear();
        gout << move_to(0, 0) << color(0, 0, 0) << box(_X, _Y);
        gout << move_to(_X/2-gout.twidth(str2)/2, _Y/2) << color(255, 255, 255) << text(str2) << refresh;
    }
    string irany;
};
void Checked_box::action2()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        if ((_myparent->widgets[sorszam+15])->_striped==true && (_myparent->widgets[sorszam-15])->_striped==false)
        {
            /// Row to the left
            cout << "jobbra van egy BOX" << endl;
            if (_myparent->widgets[sorszam+15]->y_eddig == 0)
            {
                _myparent->irany = "balra";
                _myparent->widgets[sorszam]->y_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->y_eddig += _myparent->widgets[sorszam+15]->y_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-15])->_striped==true && (_myparent->widgets[sorszam+15])->_striped==false)
        {
            /// Row to the right
            cout << "balra van egy BOX" << endl;
            if (_myparent->widgets[sorszam-15]->y_eddig == 0)
            {
                _myparent->irany = "jobbra";
                _myparent->widgets[sorszam]->y_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->y_eddig += _myparent->widgets[sorszam-15]->y_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-15])->_striped==true && (_myparent->widgets[sorszam+15])->_striped==true)
        {
            /// More possibilities
            _myparent->widgets[sorszam]->y_eddig = 2;
            if ((_myparent->widgets[sorszam-30])->_striped==true && (_myparent->widgets[sorszam+30])->_striped==true)
            {
                //cout << "Negy koze raktal" << endl;
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam-45])->_striped==true && (_myparent->widgets[sorszam-30])->_striped==true &&
                     (_myparent->widgets[sorszam+15])->_striped==true && (_myparent->widgets[sorszam-15])->_striped==true)
            {
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam+45])->_striped==true && (_myparent->widgets[sorszam+30])->_striped==true &&
                     (_myparent->widgets[sorszam-15])->_striped==true && (_myparent->widgets[sorszam+15])->_striped==true)
            {
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
        }
        else if ((_myparent->widgets[sorszam-1])->_striped==true && (_myparent->widgets[sorszam+1])->_striped==false)
        {
            /// Row downwards
            cout << "feljebb van egy BOX" << endl;
            if (_myparent->widgets[sorszam-1]->y_eddig == 0)
            {
                _myparent->irany = "le";
                _myparent->widgets[sorszam]->y_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->y_eddig += _myparent->widgets[sorszam-1]->y_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam+1])->_striped==true && (_myparent->widgets[sorszam-1])->_striped==false)
        {
            /// Row upwards
            cout << "lejjebb van egy BOX" << endl;
            if (_myparent->widgets[sorszam+1]->y_eddig == 0)
            {
                _myparent->irany = "fel";
                _myparent->widgets[sorszam]->y_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->y_eddig += _myparent->widgets[sorszam+1]->y_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-1])->_striped==true && (_myparent->widgets[sorszam+1])->_striped==true)
        {
            /// Much More possibilities
            _myparent->widgets[sorszam]->y_eddig = 2;
            if ((_myparent->widgets[sorszam-2])->_striped==true && (_myparent->widgets[sorszam+2])->_striped==true)
            {
                //cout << "Negy koze raktal" << endl;
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam-3])->_striped==true && (_myparent->widgets[sorszam-2])->_striped==true &&
                     (_myparent->widgets[sorszam+1])->_striped==true && (_myparent->widgets[sorszam-1])->_striped==true)
            {
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam+3])->_striped==true && (_myparent->widgets[sorszam+2])->_striped==true &&
                     (_myparent->widgets[sorszam-1])->_striped==true && (_myparent->widgets[sorszam+1])->_striped==true)
            {
                _myparent->widgets[sorszam]->y_eddig = 4;
            }
        }
        if (_myparent->widgets[sorszam]->y_eddig > 3)
        {
            _myparent->y_gyozelem();
        }

    }
}
void Checked_box::action()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        if ((_myparent->widgets[sorszam+15])->_checked==true && (_myparent->widgets[sorszam-15])->_checked==false)
        {
            /// Row to the left
            cout << "jobbra van egy X" << endl;
            if (_myparent->widgets[sorszam+15]->x_eddig == 0)
            {
                _myparent->irany = "balra";
                _myparent->widgets[sorszam]->x_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->x_eddig += _myparent->widgets[sorszam+15]->x_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-15])->_checked==true && (_myparent->widgets[sorszam+15])->_checked==false)
        {
            /// Row to the right
            cout << "balra van egy X" << endl;
            if (_myparent->widgets[sorszam-15]->x_eddig == 0)
            {
                _myparent->irany = "jobbra";
                _myparent->widgets[sorszam]->x_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->x_eddig += _myparent->widgets[sorszam-15]->x_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-15])->_checked==true && (_myparent->widgets[sorszam+15])->_checked==true)
        {
            /// More possibilities
            _myparent->widgets[sorszam]->x_eddig = 2;
            if ((_myparent->widgets[sorszam-30])->_checked==true && (_myparent->widgets[sorszam+30])->_checked==true)
            {
                //cout << "Negy koze raktal" << endl;
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam-45])->_checked==true && (_myparent->widgets[sorszam-30])->_checked==true &&
                     (_myparent->widgets[sorszam+15])->_checked==true && (_myparent->widgets[sorszam-15])->_checked==true)
            {
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam+45])->_checked==true && (_myparent->widgets[sorszam+30])->_checked==true &&
                     (_myparent->widgets[sorszam-15])->_checked==true && (_myparent->widgets[sorszam+15])->_checked==true)
            {
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
        }
        else if ((_myparent->widgets[sorszam-1])->_checked==true && (_myparent->widgets[sorszam+1])->_checked==false)
        {
            /// Row downwards
            cout << "feljebb van egy X" << endl;
            if (_myparent->widgets[sorszam-1]->x_eddig == 0)
            {
                _myparent->irany = "le";
                _myparent->widgets[sorszam]->x_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->x_eddig += _myparent->widgets[sorszam-1]->x_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam+1])->_checked==true && (_myparent->widgets[sorszam-1])->_checked==false)
        {
            /// Row upwards
            cout << "lejjebb van egy X" << endl;
            if (_myparent->widgets[sorszam+1]->x_eddig == 0)
            {
                _myparent->irany = "fel";
                _myparent->widgets[sorszam]->x_eddig =1;
            }
            else if(_myparent->widgets[sorszam]->_checked==false && _myparent->widgets[sorszam]->_striped==false)
            {
                _myparent->widgets[sorszam]->x_eddig += _myparent->widgets[sorszam+1]->x_eddig+1;
            }

        }
        else if ((_myparent->widgets[sorszam-1])->_checked==true && (_myparent->widgets[sorszam+1])->_checked==true)
        {
            /// Much More possibilities
            _myparent->widgets[sorszam]->x_eddig = 2;
            if ((_myparent->widgets[sorszam-2])->_checked==true && (_myparent->widgets[sorszam+2])->_checked==true)
            {
                //cout << "Negy koze raktal" << endl;
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam-3])->_checked==true && (_myparent->widgets[sorszam-2])->_checked==true &&
                     (_myparent->widgets[sorszam+1])->_checked==true && (_myparent->widgets[sorszam-1])->_checked==true)
            {
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
            else if ((_myparent->widgets[sorszam+3])->_checked==true && (_myparent->widgets[sorszam+2])->_checked==true &&
                     (_myparent->widgets[sorszam-1])->_checked==true && (_myparent->widgets[sorszam+1])->_checked==true)
            {
                _myparent->widgets[sorszam]->x_eddig = 4;
            }
        }
    }
    if (_myparent->widgets[sorszam]->x_eddig > 3)
    {
        _myparent->x_gyozelem();
    }

    cout << _myparent->irany << endl;
    //cout << _myparent->x_eddig << endl;
}
/*
void Reverse_button::action() {
    _myparent->tx1->reverseText(_myparent->tx1->erteke());
}*/


int main()
{
    My_Window * mywindow = new My_Window(800,850);
    mywindow->event_loop();
    return 0;
}


