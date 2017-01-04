#ifndef LAYER_H
#define LAYER_H

#include "VisibleObject.h"
#include "AssetManager.h"
#include <vector>
#include <iostream>
#include <fstream>
class Layer
{
public:
	Layer() = delete;
	Layer(sf::RenderWindow& pwindow, AssetManager& pAssets);
	~Layer();
	void draw();
	bool update(sf::Time dt);

	void addObj(VisibleObject* obj);
	VisibleObject* getObjectUnderCursor(sf::Vector2f pos);
	void removeObj(VisibleObject* objToRemove);
	void toggleHide(){ hide = !hide; }
	bool save(std::ofstream& saveFile);
	void load(std::ifstream& loadFile);
	void clear();
private:

	bool hide;
	sf::RenderWindow& window;
	AssetManager& assets;
	std::vector<VisibleObject*>objs;

	
};

#endif