#include "Editor.h"
#include <CommCtrl.h>
#include <commdlg.h>

#include "Phys.h"

static Editor *pThis = NULL; // our "this" pointer will go here

LRESULT Editor::WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// Quit when we close the main window
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	case WM_LBUTTONDOWN:
	{
		POINT p;
		GetCursorPos(&p);
		SetFocus(WindowFromPoint(p));
	}break;
	case WM_MOVE:
	{
			
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_LOAD:
		{
			OPENFILENAMEA ofn;
			std::string szFileName(MAX_PATH, '/0');
			szFileName[0] = '\0';
			std::string szFileTitle(MAX_PATH, '/0');
			szFileTitle[0] = '\0';
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
			ofn.hwndOwner = NULL;
			ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
			ofn.lpstrFile = &szFileName[0];
			ofn.lpstrFileTitle = &szFileTitle[0];
			ofn.nMaxFile = MAX_PATH;
			ofn.nMaxFileTitle = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "png";
			
			if (GetOpenFileNameA(&ofn))
			{
				// Do something usefull with the filename stored in szFileName 
				int pos = szFileTitle.find_first_of('\0');
				std::string temp = szFileTitle.substr(0, pos);

				int posFull = szFileName.find_first_of('\0');
				std::string tempFull = szFileName.substr(0, posFull);

				if (world.getAssets().getTexture(tempFull) == NULL)
				{
					if (world.getAssets().addTexFromFullPath(tempFull, temp))
					{
						list.addToList(temp);
					}
				}
			}
		}break;
		case ID_BUTTON_NAME:
		{
			if (user.getActive())
			{
				user.getActive()->setOptName(interName.getText());
			}
		}break;
		case ID_BUTTON_NEXTWORLD:
		{
			if (user.getActive())
			{
				user.getActive()->setOptNextWorld(nextWorldName.getText());
			}
		}break;
		case ID_LISTBOX_BRUSH:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				user.getBrush().setActiveBrush(list.getSelectedName());
			}
		}break;
		case ID_COMBO_OBJTYPE:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (user.getActive())
				{
					int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					user.getActive()->setObjType(static_cast<GameObject::EObjType>(ItemIndex));
					if (ItemIndex == 3)//OBJ_INTERACT
					{
						ShowWindow(interTypeCombo, SW_SHOW);
					}
					else
					{
						ShowWindow(interTypeCombo, SW_HIDE);
					}
				}
			}
		}break;
		case ID_COMBO_INTERACT:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (user.getActive())
				{
					int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					user.getActive()->setInterType(static_cast<VisibleObject::EInteract>(ItemIndex));
				}
			}
		}break;
		}
	}break;
	case WM_NOTIFY:
	{
	}break;
	default:
	{
		
	}
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
////////////////////////////////////////////////////////////
/// Function called whenever one of our windows receives a message
///
////////////////////////////////////////////////////////////
LRESULT CALLBACK Editor::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Editor *self;
	if (message == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		self = reinterpret_cast<Editor*>(lpcs->lpCreateParams);
		SetWindowLongPtr(handle, GWLP_USERDATA,
			reinterpret_cast<LPARAM>(self));
	}
	else {
		// Recover the "this" pointer from where our WM_NCCREATE handler
		// stashed it.
		self = reinterpret_cast<Editor*>(
			GetWindowLongPtr(handle, GWLP_USERDATA));
	}
	//used self to cast if stored an Editor variable, but use pThis since it is an instance of the running Editor
	if (self)
	{
		return pThis->WindowProc(handle, message, wParam, lParam);
	}
	return DefWindowProc(handle, message, wParam, lParam);
}

Editor::Editor() : eView(window), user(window, &eView, world, &physMenu), world(window)
{
	noUpdate = false;
	pThis = this;
	instance = GetModuleHandle(NULL);

	// Define a class for our main window
	WNDCLASS windowClass;
	windowClass.style = 0;
	windowClass.lpfnWndProc = Editor::onEvent;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = NULL;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = TEXT("SFML App");
	RegisterClass(&windowClass);
	
	// Let's create the main window
	hwindow = CreateWindow(TEXT("SFML App"), TEXT("Level Editor"), SS_NOTIFY | WS_SYSMENU | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 1920, 1040, NULL, NULL, instance, pThis);
	
	// add a static window to display where to put other controls
	propWindow = CreateWindow(TEXT("STATIC"), TEXT("Textures:"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 1600, 0, 320, 1040, hwindow, NULL, instance, NULL);
	
	interName.init(hwindow, 1600, 230, 200, 30);
	CreateWindow(TEXT("BUTTON"), TEXT("Ok"), WS_CHILD | WS_VISIBLE, 1810, 230, 40, 30, hwindow, (HMENU)ID_BUTTON_NAME, instance, NULL);
	nextWorldName.init(hwindow, 1600, 270, 200, 30);
	CreateWindow(TEXT("BUTTON"), TEXT("Ok"), WS_CHILD | WS_VISIBLE, 1810, 270, 40, 30, hwindow, (HMENU)ID_BUTTON_NEXTWORLD, instance, NULL);

	list.init(hwindow, 1605, 20, 200, 100, ID_LISTBOX_BRUSH);
	CreateWindow(TEXT("STATIC"), TEXT("Object Type:"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 130, 320, 20, propWindow, NULL, instance, NULL);
	
	objTypeCombo = CreateWindowA(WC_COMBOBOXA, NULL, CBS_DROPDOWN| WS_CHILD | WS_VISIBLE, 1600, 150, 200, 100, hwindow, (HMENU)ID_COMBO_OBJTYPE, instance, NULL);
	SendMessageA(objTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Default");
	SendMessageA(objTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Phys");
	SendMessageA(objTypeCombo, CB_ADDSTRING, 0, (LPARAM)"PlayerStart");
	SendMessageA(objTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Interact");
	SendMessageA(objTypeCombo, CB_SETCURSEL, 0, 0);

	interTypeCombo = CreateWindowA(WC_COMBOBOXA, NULL, CBS_DROPDOWN | WS_CHILD , 1600, 190, 200, 100, hwindow, (HMENU)ID_COMBO_INTERACT, instance, NULL);
	SendMessageA(interTypeCombo, CB_ADDSTRING, 0, (LPARAM)"None");
	SendMessageA(interTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Health");
	SendMessageA(interTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Key");
	SendMessageA(interTypeCombo, CB_ADDSTRING, 0, (LPARAM)"Door");



	physMenu.init(hwindow, 1600, 500, 320, 500);

	buttonLoad = CreateWindow(TEXT("BUTTON"), TEXT("Load"), WS_CHILD | WS_VISIBLE, 1810, 0, 40, 30, hwindow, (HMENU)ID_BUTTON_LOAD, instance, NULL);
	
	window.create(hwindow);
	eView.init();

	std::vector<std::string> assetNames = world.getAssets().getTextureNames();
	for (int i = 0; i < assetNames.size(); i++)
	{
		list.addToList(assetNames[i]);
	}
	user.getBrush().init(&world.getAssets());
}

int Editor::run()
{
	sf::Clock clock;
	MSG messages;
	messages.message = static_cast<UINT>(~WM_QUIT);
	while (messages.message != WM_QUIT)
	{
		if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
		{
			/* Translate virtual-key messages into character messages */
			TranslateMessage(&messages);
			/* Send message to WindowProcedure */
			DispatchMessage(&messages);
		}
		else
		{
			//SetActiveWindow(sfmlWindow);
			this->processEvent();
			if (user.updateProperties)
			{
				setProperties();
				user.updateProperties = false;
			}
			this->update(clock.restart());
			this->draw();
		}
	}

	// Destroy the main window (all its child controls will be destroyed)
	DestroyWindow(hwindow);

	// Don't forget to unregister the window class
	UnregisterClass(TEXT("SFML App"), instance);

	return 0;
}

void Editor::processEvent()
{
	sf::Event e;
	user.processEvents();
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::LostFocus)
		{
			noUpdate = true;
		}
		if (e.type == sf::Event::GainedFocus)
		{
			noUpdate = false;
		}
		user.processEvent(e);
	}
	
}

void Editor::update(sf::Time dt)
{
	if (noUpdate == false)
	{
		user.update(dt);
		//newText.setText(std::to_string(obj.getRotation()));
	}
}

void Editor::draw()
{
	window.clear();
	eView.setView(EditorView::EDrawView::DRAWVIEW_BACKGROUND);
	world.draw(World::ELayer::EL_BACKGROUND_BACK);
	world.draw(World::ELayer::EL_BACKGROUND_FRONT);

	eView.setView(EditorView::EDrawView::DRAWVIEW_FOREGROUND);
	world.draw(World::ELayer::EL_PLAYGROUND_BACK);
	world.draw(World::ELayer::EL_PLAYGROUND_MID);
	world.draw(World::ELayer::EL_PLAYGROUND_FRONT);
	world.draw(World::ELayer::EL_PHYS);
	user.draw();


	window.display();
}

void Editor::setProperties()
{
	if (user.getActive())
	{
		SendMessageA(objTypeCombo, CB_SETCURSEL, user.getActive()->getObjType(), 0);
		SendMessageA(interTypeCombo, CB_SETCURSEL, user.getActive()->getInterType(), 0);
		if (user.getActive()->getObjType() == GameObject::EObjType::OBJ_INTERACT)//OBJ_INTERACT
		{
			ShowWindow(interTypeCombo, SW_SHOW);
		}
		else
		{
			ShowWindow(interTypeCombo, SW_HIDE);
		}
		interName.setText(user.getActive()->getOptName());
		nextWorldName.setText(user.getActive()->getOptNextWorld());
	}
}