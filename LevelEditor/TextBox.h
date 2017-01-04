#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <Windows.h>
#include <string>
class TextBox
{
public:
	TextBox();
	void init(HWND& window, int x, int y, int sizex, int sizey);
	std::string getText();
	void setText(std::string newStr);
//private:
	HWND textBox;
	std::string text;

};

#endif