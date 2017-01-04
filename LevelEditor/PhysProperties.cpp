#include "PhysProperties.h"

PhysProperties::PhysProperties()
{

}

void PhysProperties::init(HWND& pParent, int posx, int posy, int sizex, int sizey)
{
	CreateWindow(TEXT("STATIC"), TEXT("Primitive"), WS_CHILD | WS_VISIBLE , posx, posy, sizex, 20, pParent, NULL, GetModuleHandle(NULL), NULL);
	physPrim.init(pParent, posx, posy + 20, 200, 100, ID_COMBO_PHYSPRIM);
	physPrim.addString("PHYS_PRIM_LINE");
	physPrim.addString("PHYS_PRIM_TRI");
	physPrim.addString("PHYS_PRIM_QUAD");
	physPrim.setSelected(2);

	CreateWindow(TEXT("STATIC"), TEXT("Property"), WS_CHILD | WS_VISIBLE, posx, posy + 50, sizex, 20, pParent, NULL, GetModuleHandle(NULL), NULL);
	physProp.init(pParent, posx, posy + 70, 200, 100, ID_COMBO_PHYSPROP);
	physProp.addString("Default");
	physProp.addString("Ice");
	physProp.addString("Rubber");
	physProp.addString("Sticky");
	physProp.addString("Death");
	physProp.setSelected(0);
}

int PhysProperties::getPrim()
{
	return physPrim.getSelected();
}

int PhysProperties::getProp()
{
	return physProp.getSelected();
}