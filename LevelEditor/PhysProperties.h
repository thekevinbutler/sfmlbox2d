#ifndef PHYSPROPERTIES_H
#define PHYSPROPERTIES_H

#include "ComboBox.h"
#define ID_COMBO_PHYSPRIM 103
#define ID_COMBO_PHYSPROP 104

class PhysProperties
{
public:
	PhysProperties();
	void init(HWND& pParent, int posx, int posy, int sizex, int sizey);
	int getPrim();
	int getProp();
	//call if activeObj is physic object that has custom properties
	void setProp();
private:
	ComboBox physPrim;
	ComboBox physProp;
};

#endif