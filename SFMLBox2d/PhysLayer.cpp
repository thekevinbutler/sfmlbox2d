#include "PhysLayer.h"

PhysLayer::PhysLayer(sf::RenderWindow& pWindow, b2World& pWorld) : window(pWindow), world(pWorld)
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

void PhysLayer::load(std::ifstream& loadFile)
{
	//load object count
	int objCount = 0;
	loadFile >> objCount;

	//for through the object count and create Phys objects
	for (int i = 0; i < objCount; i++)
	{
		Phys* phys = new Phys(world, Phys::EPhysPrim::PHYS_PRIM_QUAD, Phys::EPhysProperties::PHYS_PROP_DEFAULT);
		phys->load(loadFile);
		addPhys(phys);
	}
}

void PhysLayer::clear()
{
	for (std::vector<Phys*>::iterator it = physObjs.begin(); it != physObjs.end(); ++it) {
		delete *it;
	}
}