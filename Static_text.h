#ifndef STATIC_TEXT_H
#define STATIC_TEXT_H

#include <vector>
#include "graphics.hpp"
#include "widgets.hpp"

class Static_text : public Widget
{
protected:
    bool _focused;
    std::string _felirat;
public:
    Static_text(int x, int y, int sx, int sy, int menu_tipus, std::string felirat);
    virtual bool is_focused();
    virtual std::string erteke(){return _felirat;}
    virtual void draw() const;
    virtual void handle(genv::event ev){};
    void setText(std::string s) {_felirat=s;}
    void reverseText(std::string s) {
		for (int i = 0; i < s.length()+1; i++) {
			_felirat[i] = s[s.length()-i-1];
		}
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
        return false;
    }
};
#endif // STATIC_TEXT_H
