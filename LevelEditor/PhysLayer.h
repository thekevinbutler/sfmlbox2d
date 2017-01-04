#ifndef PHYSLAYER_H
#define PHYSLAYER_H

#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "Phys.h"

class PhysLayer
{
public:
	PhysLayer(sf::RenderWindow& pWindow);
	void addPhys(Phys* newObj);
	void draw();

	Phys* getObjectUnderCursor(sf::Vector2f pos);
	void removeObj(Phys* objToRemove);
	void toggleHide(){ hide = !hide; }
	bool save(std::ofstream& saveFile);
private:
	bool hide;
	sf::RenderWindow& window;
	std::vector<Phys*> physObjs;

};


#endif