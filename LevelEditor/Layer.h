#ifndef LAYER_H
#define LAYER_H

#include "VisibleObject.h"
#include <vector>
#include <iostream>
#include <fstream>
class Layer
{
public:
	Layer() = delete;
	Layer(sf::RenderWindow& pwindow);

	void draw();

	void addObj(VisibleObject* obj);
	VisibleObject* getObjectUnderCursor(sf::Vector2f pos);
	void removeObj(VisibleObject* objToRemove);
	void toggleHide(){ hide = !hide; }
	bool save(std::ofstream& saveFile);
private:
	
	bool hide;
	sf::RenderWindow& window;
	std::vector<VisibleObject*>objs;
	
};

#endif