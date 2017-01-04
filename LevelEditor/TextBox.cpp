#include "TextBox.h"

TextBox::TextBox()
{
}

void TextBox::init(HWND& window, int x, int y, int sizex, int sizey)
{
	textBox = CreateWindow(TEXT("EDIT"), TEXT(""), WS_BORDER | WS_CHILD | WS_VISIBLE, x, y, sizex, sizey, window, NULL, GetModuleHandle(NULL), NULL);

}

std::string TextBox::getText()
{
	int bufferLen = GetWindowTextLength(textBox) + 1; // why send the message twice?
	std::string data(bufferLen, '\0');
	GetWindowTextA(textBox, &data[0], bufferLen);
	text = data;
	return text;
}

void TextBox::setText(std::string newStr)
{
	text = newStr;
	SetWindowTextA(textBox, text.c_str());
}