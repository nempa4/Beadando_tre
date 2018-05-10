#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "graphics.hpp"
#include "widgets.hpp"
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
        gout << move_to(_x+2, _y+2) << color(50, 50, 50) << box(_size_x-4, _size_y-4);
        if (_focused)
        {
            gout << move_to(_x, _y) << color(255,255,0) << box(_size_x, _size_y);
            gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
        }
        if (_checked)
        {
            gout << move_to(_x+2, _y+2) << color(30, 30, 30) << box(_size_x-4, _size_y-4);
            gout << color(255,0,0);
            gout << move_to(_x+_size_x/4, _y+_size_y/4) << line(_size_x-_size_x/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x/4+1, _y+_size_y/4) << line(_size_x-_size_y/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x-_size_x/4, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
            gout << move_to(_x+_size_x-_size_x/4-1, _y+_size_y/4) << line(-_size_x+_size_y/2, _size_y-_size_y/2);
        }
        if (_striped)
        {
            gout << move_to(_x+2, _y+2) << color(30, 30, 30) << box(_size_x-4, _size_y-4);
            gout << color(0,0,255);
            gout << move_to(_x+_size_x/4, _y+_size_y/4) << box(_size_x/2, _size_y/2);
            //gout << move_to(_x+_size_x/3, _y+4) << box(_size_x_size_x/3, _size_y-8);
        }
    }
    virtual void action();
    virtual void _action();
    virtual void __action();
    virtual void action2();
    virtual void _action2();
    virtual void __action2();
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

            if (!_checked) action();
            if (!_checked) _action();
            if (!_checked) __action();
            std::cout << sorszam << std::endl;
            /*std::cout << x_eddig << std::endl;
            std::cout << y_eddig << std::endl;*/
            //std::cout << irany << std::endl;
            if (!_checked && !_striped)
            {
                _checked = true;
            }
        }
        if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_right)
        {
            std::cout << sorszam << std::endl;
            if (!_striped) action2();
            if (!_striped) _action2();
            if (!_striped) __action2();
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
                /*if (j!=0)
                {*/
                ckb1->sorszam = i*15+j;
                /*}
                else
                {
                    ckb1->sorszam = i*10+j;
                }*/
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
};

void Checked_box::action()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        /// GAME RULEZ
        /*	cout << _myparent->widgets[sorszam-60]->_checked << endl;
        	cout << _myparent->widgets[sorszam-45]->_checked << endl;
        	cout << _myparent->widgets[sorszam-30]->_checked << endl;
        	cout << _myparent->widgets[sorszam-15]->_checked << endl << endl;

        	cout << _myparent->widgets[sorszam+15]->_checked << endl;
        	cout << _myparent->widgets[sorszam+30]->_checked << endl;
        	cout << _myparent->widgets[sorszam+45]->_checked << endl;
        	cout << _myparent->widgets[sorszam+60]->_checked << endl;*/

        /// /////////////////////////////////////////////////////////////////// JOBB-BAL ///////////////////////////////////////////////////////////////////////////////////////////
        if (_myparent->widgets[sorszam]->sorszam > 209 && _myparent->widgets[sorszam]->sorszam < 225)
        {
            if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam-60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BALRA VANNAK
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 0 && _myparent->widgets[sorszam]->sorszam < 15)
        {
            if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam+60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBBRA VANNAK
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 194 && _myparent->widgets[sorszam]->sorszam < 210)
        {
            if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam-60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BALRA VANNAK
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 15 && _myparent->widgets[sorszam]->sorszam < 30)
        {
            if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam+60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBBRA VANNAK
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 179 && _myparent->widgets[sorszam]->sorszam < 195)
        {
            if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam-60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BALRA VANNAK
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 30 && _myparent->widgets[sorszam]->sorszam < 45)
        {
            if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam+60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBBRA VANNAK
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }//////
        else if (_myparent->widgets[sorszam]->sorszam > 164 && _myparent->widgets[sorszam]->sorszam < 180)
        {
            if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam-60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BALRA VANNAK
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam-15]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 45 && _myparent->widgets[sorszam]->sorszam < 60)
        {
            if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam+60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBBRA VANNAK
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam+15]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
            }
        }///
        else
        {
            if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam+60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBBRA VANNAK
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam-60]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BALRA VANNAK
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked && _myparent->widgets[sorszam-15]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam+15]->_checked && _myparent->widgets[sorszam+30]->_checked && _myparent->widgets[sorszam+45]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
            }
            else if (_myparent->widgets[sorszam-15]->_checked && _myparent->widgets[sorszam-30]->_checked && _myparent->widgets[sorszam-45]->_checked && _myparent->widgets[sorszam+15]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
            }
            else
            {
                _myparent->widgets[sorszam]->x_win = false;
            }
        }
    }
    if (_myparent->widgets[sorszam]->x_win)
    {
        _myparent->x_gyozelem();
    }

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        /// /////////////////////////////////////////////////////////////////// FEL-LE ///////////////////////////////////////////////////////////////////////////////////////////
        if (_myparent->widgets[sorszam]->sorszam == 14 || _myparent->widgets[sorszam]->sorszam == 29 || _myparent->widgets[sorszam]->sorszam == 44 || _myparent->widgets[sorszam]->sorszam == 59
                || _myparent->widgets[sorszam]->sorszam == 74 || _myparent->widgets[sorszam]->sorszam == 89 || _myparent->widgets[sorszam]->sorszam == 104 || _myparent->widgets[sorszam]->sorszam == 119
                || _myparent->widgets[sorszam]->sorszam == 134 || _myparent->widgets[sorszam]->sorszam == 149 || _myparent->widgets[sorszam]->sorszam == 164 || _myparent->widgets[sorszam]->sorszam == 179
                || _myparent->widgets[sorszam]->sorszam == 194 || _myparent->widgets[sorszam]->sorszam == 209 || _myparent->widgets[sorszam]->sorszam == 224)
        {
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// FELFELÉ VANNAK
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam == 0 || _myparent->widgets[sorszam]->sorszam == 15 || _myparent->widgets[sorszam]->sorszam == 30 || _myparent->widgets[sorszam]->sorszam == 45
                 || _myparent->widgets[sorszam]->sorszam == 60 || _myparent->widgets[sorszam]->sorszam == 75 || _myparent->widgets[sorszam]->sorszam == 90 || _myparent->widgets[sorszam]->sorszam == 105
                 || _myparent->widgets[sorszam]->sorszam == 120 || _myparent->widgets[sorszam]->sorszam == 135 || _myparent->widgets[sorszam]->sorszam == 150 || _myparent->widgets[sorszam]->sorszam == 165
                 || _myparent->widgets[sorszam]->sorszam == 180 || _myparent->widgets[sorszam]->sorszam == 195 || _myparent->widgets[sorszam]->sorszam == 210)
        {
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam == 1 || _myparent->widgets[sorszam]->sorszam == 16 || _myparent->widgets[sorszam]->sorszam == 31 || _myparent->widgets[sorszam]->sorszam == 46
                 || _myparent->widgets[sorszam]->sorszam == 61 || _myparent->widgets[sorszam]->sorszam == 76 || _myparent->widgets[sorszam]->sorszam == 91 || _myparent->widgets[sorszam]->sorszam == 106
                 || _myparent->widgets[sorszam]->sorszam == 121 || _myparent->widgets[sorszam]->sorszam == 136 || _myparent->widgets[sorszam]->sorszam == 151 || _myparent->widgets[sorszam]->sorszam == 166
                 || _myparent->widgets[sorszam]->sorszam == 181 || _myparent->widgets[sorszam]->sorszam == 196 || _myparent->widgets[sorszam]->sorszam == 211)
        {
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }

        }
        else if (_myparent->widgets[sorszam]->sorszam == 2 || _myparent->widgets[sorszam]->sorszam == 17 || _myparent->widgets[sorszam]->sorszam == 32 || _myparent->widgets[sorszam]->sorszam == 47
                 || _myparent->widgets[sorszam]->sorszam == 62 || _myparent->widgets[sorszam]->sorszam == 77 || _myparent->widgets[sorszam]->sorszam == 92 || _myparent->widgets[sorszam]->sorszam == 107
                 || _myparent->widgets[sorszam]->sorszam == 122 || _myparent->widgets[sorszam]->sorszam == 137 || _myparent->widgets[sorszam]->sorszam == 152 || _myparent->widgets[sorszam]->sorszam == 167
                 || _myparent->widgets[sorszam]->sorszam == 182 || _myparent->widgets[sorszam]->sorszam == 197 || _myparent->widgets[sorszam]->sorszam == 212)
		{
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
		else if (_myparent->widgets[sorszam]->sorszam == 3|| _myparent->widgets[sorszam]->sorszam == 18 || _myparent->widgets[sorszam]->sorszam == 33 || _myparent->widgets[sorszam]->sorszam == 48
                 || _myparent->widgets[sorszam]->sorszam == 63 || _myparent->widgets[sorszam]->sorszam == 78 || _myparent->widgets[sorszam]->sorszam == 93 || _myparent->widgets[sorszam]->sorszam == 108
                 || _myparent->widgets[sorszam]->sorszam == 123 || _myparent->widgets[sorszam]->sorszam == 138 || _myparent->widgets[sorszam]->sorszam == 153 || _myparent->widgets[sorszam]->sorszam == 168
                 || _myparent->widgets[sorszam]->sorszam == 183 || _myparent->widgets[sorszam]->sorszam == 198 || _myparent->widgets[sorszam]->sorszam == 213)
		{
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
		else if (_myparent->widgets[sorszam]->sorszam == 4 || _myparent->widgets[sorszam]->sorszam == 19 || _myparent->widgets[sorszam]->sorszam == 34 || _myparent->widgets[sorszam]->sorszam == 49
                 || _myparent->widgets[sorszam]->sorszam == 64 || _myparent->widgets[sorszam]->sorszam == 79 || _myparent->widgets[sorszam]->sorszam == 94 || _myparent->widgets[sorszam]->sorszam == 109
                 || _myparent->widgets[sorszam]->sorszam == 124 || _myparent->widgets[sorszam]->sorszam == 139 || _myparent->widgets[sorszam]->sorszam == 154 || _myparent->widgets[sorszam]->sorszam == 169
                 || _myparent->widgets[sorszam]->sorszam == 184 || _myparent->widgets[sorszam]->sorszam == 199 || _myparent->widgets[sorszam]->sorszam == 214)
		{
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
		else if (_myparent->widgets[sorszam]->sorszam == 223 || _myparent->widgets[sorszam]->sorszam == 208 || _myparent->widgets[sorszam]->sorszam == 193 || _myparent->widgets[sorszam]->sorszam == 178
                 || _myparent->widgets[sorszam]->sorszam == 163 || _myparent->widgets[sorszam]->sorszam == 148 || _myparent->widgets[sorszam]->sorszam == 133 || _myparent->widgets[sorszam]->sorszam == 118
                 || _myparent->widgets[sorszam]->sorszam == 103 || _myparent->widgets[sorszam]->sorszam == 88 || _myparent->widgets[sorszam]->sorszam == 73 || _myparent->widgets[sorszam]->sorszam == 58
                 || _myparent->widgets[sorszam]->sorszam == 43 || _myparent->widgets[sorszam]->sorszam == 28 || _myparent->widgets[sorszam]->sorszam == 13)
        {
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }

        }
        else if (_myparent->widgets[sorszam]->sorszam == 222 || _myparent->widgets[sorszam]->sorszam == 207 || _myparent->widgets[sorszam]->sorszam == 192 || _myparent->widgets[sorszam]->sorszam == 177
                 || _myparent->widgets[sorszam]->sorszam == 162 || _myparent->widgets[sorszam]->sorszam == 147 || _myparent->widgets[sorszam]->sorszam == 132 || _myparent->widgets[sorszam]->sorszam == 117
                 || _myparent->widgets[sorszam]->sorszam == 102 || _myparent->widgets[sorszam]->sorszam == 87 || _myparent->widgets[sorszam]->sorszam == 72 || _myparent->widgets[sorszam]->sorszam == 57
                 || _myparent->widgets[sorszam]->sorszam == 42 || _myparent->widgets[sorszam]->sorszam == 27 || _myparent->widgets[sorszam]->sorszam == 12)
		{
			if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
		else if (_myparent->widgets[sorszam]->sorszam == 221 || _myparent->widgets[sorszam]->sorszam == 206 || _myparent->widgets[sorszam]->sorszam == 191|| _myparent->widgets[sorszam]->sorszam == 176
                 || _myparent->widgets[sorszam]->sorszam == 161 || _myparent->widgets[sorszam]->sorszam == 146 || _myparent->widgets[sorszam]->sorszam == 131 || _myparent->widgets[sorszam]->sorszam == 116
                 || _myparent->widgets[sorszam]->sorszam == 101 || _myparent->widgets[sorszam]->sorszam == 86 || _myparent->widgets[sorszam]->sorszam == 71 || _myparent->widgets[sorszam]->sorszam == 56
                 || _myparent->widgets[sorszam]->sorszam == 41 || _myparent->widgets[sorszam]->sorszam == 26 || _myparent->widgets[sorszam]->sorszam == 11)
		{
			if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
		else if (_myparent->widgets[sorszam]->sorszam == 220 || _myparent->widgets[sorszam]->sorszam == 205 || _myparent->widgets[sorszam]->sorszam == 190|| _myparent->widgets[sorszam]->sorszam == 175
                 || _myparent->widgets[sorszam]->sorszam == 160 || _myparent->widgets[sorszam]->sorszam == 145 || _myparent->widgets[sorszam]->sorszam == 130 || _myparent->widgets[sorszam]->sorszam == 115
                 || _myparent->widgets[sorszam]->sorszam == 100 || _myparent->widgets[sorszam]->sorszam == 85 || _myparent->widgets[sorszam]->sorszam == 70 || _myparent->widgets[sorszam]->sorszam == 55
                 || _myparent->widgets[sorszam]->sorszam == 40 || _myparent->widgets[sorszam]->sorszam == 25 || _myparent->widgets[sorszam]->sorszam == 10)
		{
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
			if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
		}
        else
        {
            if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam+4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
            }
            else if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam-4]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// FELFELÉ VANNAK
            }
            else if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
            }
            else if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked && _myparent->widgets[sorszam-1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
            }
            else if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam+1]->_checked && _myparent->widgets[sorszam+2]->_checked && _myparent->widgets[sorszam+3]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
            }
            else if (_myparent->widgets[sorszam-1]->_checked && _myparent->widgets[sorszam-2]->_checked && _myparent->widgets[sorszam-3]->_checked && _myparent->widgets[sorszam+1]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
            }
            else
            {
                _myparent->widgets[sorszam]->x_win = false;
            }
        }
        if (_myparent->widgets[sorszam]->x_win)
        {
            _myparent->x_gyozelem();
        }
    }
}
/// ///////////////////////////////////////////////////////////////////// ÁTLÓ BAL-FELÜLRŐL JOBB-ALULRA//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checked_box::_action()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        if (_myparent->widgets[sorszam]->sorszam == 74 || _myparent->widgets[sorszam]->sorszam == 89 || _myparent->widgets[sorszam]->sorszam == 104 || _myparent->widgets[sorszam]->sorszam == 119
                || _myparent->widgets[sorszam]->sorszam == 134 || _myparent->widgets[sorszam]->sorszam == 149 || _myparent->widgets[sorszam]->sorszam == 164 || _myparent->widgets[sorszam]->sorszam == 179
                || _myparent->widgets[sorszam]->sorszam == 194 || _myparent->widgets[sorszam]->sorszam == 209 || _myparent->widgets[sorszam]->sorszam == 224)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// ALSÓ SOR KIKVÉTEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam == 0 || _myparent->widgets[sorszam]->sorszam == 150 || _myparent->widgets[sorszam]->sorszam == 15 || _myparent->widgets[sorszam]->sorszam == 30
                 || _myparent->widgets[sorszam]->sorszam == 45 || _myparent->widgets[sorszam]->sorszam == 60 || _myparent->widgets[sorszam]->sorszam == 75 || _myparent->widgets[sorszam]->sorszam == 90
                 || _myparent->widgets[sorszam]->sorszam == 105 || _myparent->widgets[sorszam]->sorszam == 120 || _myparent->widgets[sorszam]->sorszam == 135)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// FELSŐ SOR KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 213 && _myparent->widgets[sorszam]->sorszam < 225)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam < 214 && _myparent->widgets[sorszam]->sorszam > 209) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 0 && _myparent->widgets[sorszam]->sorszam < 11)
        {
            //cout << _myparent->widgets[sorszam+16]->_checked << endl << _myparent->widgets[sorszam+32]->_checked << endl << _myparent->widgets[sorszam+48]->_checked << endl << _myparent->widgets[sorszam+64]->_checked << endl;
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 10 && _myparent->widgets[sorszam]->sorszam < 15) {}
        else if (_myparent->widgets[sorszam]->sorszam > 197 && _myparent->widgets[sorszam]->sorszam < 210)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 194 && _myparent->widgets[sorszam]->sorszam < 198) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 15 && _myparent->widgets[sorszam]->sorszam < 27)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 26 && _myparent->widgets[sorszam]->sorszam < 30) {}
        else if (_myparent->widgets[sorszam]->sorszam > 179 && _myparent->widgets[sorszam]->sorszam < 195)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 179 && _myparent->widgets[sorszam]->sorszam < 182) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 30 && _myparent->widgets[sorszam]->sorszam < 45)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 42 && _myparent->widgets[sorszam]->sorszam < 45) {}
        else if (_myparent->widgets[sorszam]->sorszam > 164 && _myparent->widgets[sorszam]->sorszam < 180)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 45 && _myparent->widgets[sorszam]->sorszam < 60)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
            }
        }
        else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
        }
        else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// FELFELÉ VANNAK
        }
        else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
        }
        else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
        }
        else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
        }
        else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
        }
        else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
        }
        else
        {
            _myparent->widgets[sorszam]->x_win = false;
        }
    }
    if (_myparent->widgets[sorszam]->x_win)
    {
        _myparent->x_gyozelem();
    }
}
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// //////////////////////////////////////////////////////////////////////////// ÁTLÓ BALRA-LE, JOBBRA-FEL /////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Checked_box::__action()
{
	if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {
        if (_myparent->widgets[sorszam]->sorszam == 164 || _myparent->widgets[sorszam]->sorszam == 89 || _myparent->widgets[sorszam]->sorszam == 104 || _myparent->widgets[sorszam]->sorszam == 119
                || _myparent->widgets[sorszam]->sorszam == 134 || _myparent->widgets[sorszam]->sorszam == 149 || _myparent->widgets[sorszam]->sorszam == 14 || _myparent->widgets[sorszam]->sorszam == 29
                || _myparent->widgets[sorszam]->sorszam == 44 || _myparent->widgets[sorszam]->sorszam == 59 || _myparent->widgets[sorszam]->sorszam == 74)
        {
        	//cout << _myparent->widgets[sorszam-14]->sorszam << _myparent->widgets[sorszam-28]->sorszam << _myparent->widgets[sorszam-42]->sorszam << _myparent->widgets[sorszam-56]->sorszam << endl;
            if (_myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam+28]->_checked && _myparent->widgets[sorszam+42]->_checked && _myparent->widgets[sorszam+56]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// ALSÓ SOR KIKVÉTEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam == 150 || _myparent->widgets[sorszam]->sorszam == 165 || _myparent->widgets[sorszam]->sorszam == 180 || _myparent->widgets[sorszam]->sorszam == 195
                 || _myparent->widgets[sorszam]->sorszam == 210 || _myparent->widgets[sorszam]->sorszam == 60 || _myparent->widgets[sorszam]->sorszam == 75 || _myparent->widgets[sorszam]->sorszam == 90
                 || _myparent->widgets[sorszam]->sorszam == 105 || _myparent->widgets[sorszam]->sorszam == 120 || _myparent->widgets[sorszam]->sorszam == 135)
        {
            if (_myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam-28]->_checked && _myparent->widgets[sorszam-42]->_checked && _myparent->widgets[sorszam-56]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// FELSŐ SOR KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 213 && _myparent->widgets[sorszam]->sorszam < 225)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam < 214 && _myparent->widgets[sorszam]->sorszam > 209) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 0 && _myparent->widgets[sorszam]->sorszam < 11)
        {
            //cout << _myparent->widgets[sorszam+16]->_checked << endl << _myparent->widgets[sorszam+32]->_checked << endl << _myparent->widgets[sorszam+48]->_checked << endl << _myparent->widgets[sorszam+64]->_checked << endl;
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 10 && _myparent->widgets[sorszam]->sorszam < 15) {}
        else if (_myparent->widgets[sorszam]->sorszam > 197 && _myparent->widgets[sorszam]->sorszam < 210)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 194 && _myparent->widgets[sorszam]->sorszam < 198) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 15 && _myparent->widgets[sorszam]->sorszam < 27)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 26 && _myparent->widgets[sorszam]->sorszam < 30) {}
        else if (_myparent->widgets[sorszam]->sorszam > 179 && _myparent->widgets[sorszam]->sorszam < 195)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 179 && _myparent->widgets[sorszam]->sorszam < 182) {}
        else if (_myparent->widgets[sorszam]->sorszam >= 30 && _myparent->widgets[sorszam]->sorszam < 45)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam > 42 && _myparent->widgets[sorszam]->sorszam < 45) {}
        else if (_myparent->widgets[sorszam]->sorszam > 164 && _myparent->widgets[sorszam]->sorszam < 180)
        {
            if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam-64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// JOBB SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
            }
        }
        else if (_myparent->widgets[sorszam]->sorszam >= 45 && _myparent->widgets[sorszam]->sorszam < 60)
        {
            if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam+64]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam+48]->_checked && _myparent->widgets[sorszam-16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// BAL SZÉL KIVETEL
            }
            else if (_myparent->widgets[sorszam+16]->_checked && _myparent->widgets[sorszam+32]->_checked && _myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
            }
            else if (_myparent->widgets[sorszam-16]->_checked && _myparent->widgets[sorszam-32]->_checked && _myparent->widgets[sorszam-48]->_checked && _myparent->widgets[sorszam+16]->_checked)
            {
                _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
            }
        }
        else if (_myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam+28]->_checked && _myparent->widgets[sorszam+42]->_checked && _myparent->widgets[sorszam+56]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// LEFELÉ VANNAK
        }
        else if (_myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam-28]->_checked && _myparent->widgets[sorszam-42]->_checked && _myparent->widgets[sorszam-56]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// FELFELÉ VANNAK
        }
        else if (_myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam-28]->_checked && _myparent->widgets[sorszam-42]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 1
        }
        else if (_myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam+28]->_checked && _myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam-28]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 2
        }
        else if (_myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam+28]->_checked && _myparent->widgets[sorszam+42]->_checked && _myparent->widgets[sorszam-14]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 3
        }
        else if (_myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam+14]->_checked && _myparent->widgets[sorszam+28]->_checked && _myparent->widgets[sorszam+42]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 4
        }
        else if (_myparent->widgets[sorszam-14]->_checked && _myparent->widgets[sorszam-28]->_checked && _myparent->widgets[sorszam-42]->_checked && _myparent->widgets[sorszam+14]->_checked)
        {
            _myparent->widgets[sorszam]->x_win = true; /// KÖRÜLÖTTE VANNAK 5
        }
        else
        {
            _myparent->widgets[sorszam]->x_win = false;
        }


    }
    if (_myparent->widgets[sorszam]->x_win)
    {
        _myparent->x_gyozelem();
    }

}


void Checked_box::action2()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {

    }
    if (_myparent->widgets[sorszam]->y_win)
    {
        _myparent->y_gyozelem();
    }

}


void Checked_box::_action2()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {

    }
    if (_myparent->widgets[sorszam]->y_win)
    {
        _myparent->y_gyozelem();
    }

}

void Checked_box::__action2()
{
    if (_myparent->widgets[sorszam]->_menu_tipus==0)
    {

    }
    if (_myparent->widgets[sorszam]->y_win)
    {
        _myparent->y_gyozelem();
    }

}

int main()
{
    My_Window * mywindow = new My_Window(800,850);
    mywindow->event_loop();
    return 0;
}


