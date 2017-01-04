#include "PhysLayer.h"

PhysLayer::PhysLayer(sf::RenderWindow& pWindow) : window(pWindow)
{
	hide = false;
}
void PhysLayer::addPhys(Phys* newObj)
{
	physObjs.emplace_back(newObj);
}
void PhysLayer::draw()
{
	if (!hide)
	{
		for (std::vector<Phys*>::iterator it = physObjs.begin(); it != physObjs.end(); ++it)
		{
			Phys* curObj = *it;
			window.draw(*curObj);
		}
	}
}

Phys* PhysLayer::getObjectUnderCursor(sf::Vector2f pos)
{
	for (std::vector<Phys*>::iterator it = physObjs.begin(); it != physObjs.end(); ++it)
	{
		Phys* curObj = *it;
		if (sf::FloatRect(curObj->getGlobalBounds()).contains(pos))
		{
			return curObj;
		}
	}
	return NULL;
}
void PhysLayer::removeObj(Phys* objToRemove)
{
	for (std::vector<Phys*>::iterator it = physObjs.begin(); it != physObjs.end(); ++it)
	{
		Phys* curObj = *it;
		if (curObj == objToRemove)
		{
			physObjs.erase(it);
			return;
		}
	}
}

bool PhysLayer::save(std::ofstream& saveFile)
{
	//save object count first
	saveFile << physObjs.size() << "\n";

	//for through objects and save them
	for (int i = 0; i < physObjs.size(); i++)
	{
		physObjs[i]->save(saveFile);
	}

	return true;
}