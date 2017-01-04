#ifndef COMBOBOX_H
#define COMBOBO_H

#include <Windows.h>
#include <string>
class ComboBox
{
public:
	ComboBox();
	void init(HWND& parent, int posx, int posy, int sizex, int sizey, int pID);
	void addString(std::string newStr);
	void setSelected(int index);
	int getSelected();
	int getID();
	HWND& getHWND();
private:
	HWND window;
	HWND* parent;
	int wndID;
};

#endif