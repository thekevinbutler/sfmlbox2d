#ifndef EDITOR_H
#define EDITOR_H

//testingIDS
#define ID_BUTTON_LOAD 100
#define ID_LISTBOX_BRUSH 101
#define ID_COMBO_OBJTYPE 102
#define ID_COMBO_INTERACT 103
#define ID_EDIT_OBJNAME 104
#define ID_BUTTON_NEXTWORLD 105
#define ID_BUTTON_NAME 106

#include <Windows.h>
#include "SFML\Graphics.hpp"
#include "VisibleObject.h"
#include "UserController.h"
#include "TextBox.h"
#include "EditorView.h"
#include "World.h"
#include "ListBox.h"
#include "PhysProperties.h"

class Editor
{
public:
	Editor();
	static LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	int run();

private:
	void processEvent();
	void update(sf::Time dt);
	void draw();
	void setProperties();

	//application instance
	HINSTANCE instance;
	//main window handle
	HWND hwindow;
	//User object that handles sfml window events
	UserController user;
	//sfml view manipulator
	EditorView eView;
	//main sfml window
	sf::RenderWindow window;
	//editable world
	World world;

	ListBox list;
	TextBox interName;
	TextBox nextWorldName;
	HWND buttonLoad;
	HWND propWindow;
	HWND textbox;
	HWND listBox;
	HWND objTypeCombo;
	HWND interTypeCombo;
	PhysProperties physMenu;

	//TESTING
	bool noUpdate;
};


#endif
