#include "ComboBox.h"
#include <CommCtrl.h>
//use init function
ComboBox::ComboBox()
{
}

void ComboBox::init(HWND& pWindow, int posx, int posy, int sizex, int sizey, int pID)
{
	wndID = pID;
	parent = &pWindow;
	// Create the list-view window in report view with label editing enabled.
	window = CreateWindowA(WC_COMBOBOXA,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN | WS_BORDER,
		posx, posy,
		sizex,
		sizey,
		pWindow,
		(HMENU)wndID,
		GetModuleHandle(NULL),
		NULL);
}

void ComboBox::addString(std::string newStr)
{
	SendMessageA(window, CB_ADDSTRING, 0, (LPARAM)newStr.c_str());
}
void ComboBox::setSelected(int index)
{
	SendMessageA(window, CB_SETCURSEL, index, 0);
}
int ComboBox::getSelected()
{
	return SendMessage(window, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}
int ComboBox::getID()
{
	return wndID;
}
HWND& ComboBox::getHWND()
{
	return window;
}