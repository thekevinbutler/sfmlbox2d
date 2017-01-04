#ifndef PHYSLAYER_H
#define PHYSLAYER_H

#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "Phys.h"
#include "Box2D\Box2D.h"

class PhysLayer
{
public:
	PhysLayer(sf::RenderWindow& pWindow, b2World& pWorld);
	void addPhys(Phys* newObj);
	void draw();

	Phys* getObjectUnderCursor(sf::Vector2f pos);
	void removeObj(Phys* objToRemove);
	void toggleHide(){ hide = !hide; }
	bool save(std::ofstream& saveFile);
	void load(std::ifstream& loadFile);
	void clear();
private:
	b2World& world;
	bool hide;
	sf::RenderWindow& window;
	std::vector<Phys*> physObjs;

};


#endif