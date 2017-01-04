#include "Layer.h"


Layer::Layer(sf::RenderWindow& pwindow) : window(pwindow)
{
	hide = false;
}

void Layer::draw()
{
	if (!hide)
	{
		for (std::vector<VisibleObject*>::iterator it = objs.begin(); it != objs.end(); ++it)
		{
			VisibleObject* curObj = *it;
			window.draw(*curObj);
		}
	}
}


void Layer::addObj(VisibleObject* obj)
{
	objs.emplace_back(obj);
}


VisibleObject* Layer::getObjectUnderCursor(sf::Vector2f pos)
{
	for (std::vector<VisibleObject*>::iterator it = objs.begin(); it != objs.end(); ++it)
	{
		VisibleObject* curObj = *it;
		if (curObj->occupiesPos(pos))
		{
			return curObj;
		}
	}
	return NULL;
}

void Layer::removeObj(VisibleObject* objToRemove)
{
	for (std::vector<VisibleObject*>::iterator it = objs.begin(); it != objs.end(); ++it)
	{
		VisibleObject* curObj = *it;
		if (curObj == objToRemove)
		{
			objs.erase(it);
			return;
		}
	}
}

bool Layer::save(std::ofstream& saveFile)
{
	//save object count
	saveFile << objs.size() << std::endl;

	//for through obj vector and save each object
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->save(saveFile);
	}

	return true;
}