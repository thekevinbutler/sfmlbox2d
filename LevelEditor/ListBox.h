#ifndef LISTBOX_H
#define LISTBOX_H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
class ListBox
{
public:
	ListBox();
	void init(HWND& window, int x, int y, int sizex, int sizey, int pID = 200);
	void addToList(std::string text);
	std::string getSelectedName();
	int getID() { return listBoxID; }
	HWND& getHWND() { return listBox; }
private:
	HWND* parent;
	HWND listBox;
	int listBoxID;
};

#endif