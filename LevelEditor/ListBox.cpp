#include "ListBox.h"
#include "resource.h"


struct PETINFO
{
	TCHAR szKind[10];
	TCHAR szBreed[50];
	TCHAR szPrice[20];
};
	
PETINFO rgPetInfo[ ] = 
{
	{TEXT("Dog"),  TEXT("Poodle"),     TEXT("$300.00")},
	{TEXT("Cat"),  TEXT("Siamese"),    TEXT("$100.00")},
	{TEXT("Fish"), TEXT("Angel Fish"), TEXT("$10.00")},
	{TEXT("Bird"), TEXT("Parakeet"),   TEXT("$5.00")},
	{TEXT("Toad"), TEXT("Woodhouse"),  TEXT("$0.25")},
};


ListBox::ListBox()
{
}



void ListBox::init(HWND& window, int x, int y, int sizex, int sizey, int pID)
{
	listBoxID = pID;
	parent = &window;
	// Create the list-view window in report view with label editing enabled.
	listBox = CreateWindow(WC_LISTBOX,
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | WS_BORDER,
		x, y,
		sizex,
		sizey,
		window,
		(HMENU)listBoxID,
		GetModuleHandle(NULL),
		NULL);
}

void ListBox::addToList(std::string text)
{
	int pos = (int)SendDlgItemMessageA(*parent, listBoxID, LB_ADDSTRING, 0, (LPARAM)text.c_str());
	
}
std::string ListBox::getSelectedName()
{
	//int pos = -1;
	//pos = (int)SendDlgItemMessageA(*parent, listBoxID, LB_GETCURSEL, 0, 0);
	int bufferLen = 20;

	std::string chBuffer(bufferLen, '\0');

	DWORD dwSel = SendDlgItemMessage(*parent, listBoxID, LB_GETCURSEL, 0, 0);

	//if has a current selection
	if (dwSel != LB_ERR)
	{
		SendDlgItemMessageA(*parent, listBoxID, LB_GETTEXT, dwSel, (LPARAM)(LPSTR)&chBuffer[0]);
		int pos = chBuffer.find_first_of('\0');
		std::string temp = chBuffer.substr(0, pos);
		return temp;
	}
	//return "" if nothing selected
	return "";
	
}