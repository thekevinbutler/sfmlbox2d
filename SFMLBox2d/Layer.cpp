#include "Layer.h"
#include "InteractObject.h"
#include "InteactHealth.h"
#include "InteractKey.h"
#include "InteractDoor.h"
Layer::Layer(sf::RenderWindow& pwindow, AssetManager& pAssets) : window(pwindow), assets(pAssets)
{
	hide = false;
}
Layer::~Layer()
{
	objs.clear();
}
void Layer::clear()
{
	objs.clear();
}
bool Layer::update(sf::Time dt)
{
	for (int i = 0; i < objs.size(); i++)
	{
		//if update returns false, then object wants destroyed
		if (!objs[i]->update(dt))
		{
			removeObj(objs[i]);
		}
	}
	return true;
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
			delete curObj;
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

void Layer::load(std::ifstream& loadFile)
{
	//load obj count
	int objCount = 0;
	loadFile >> objCount;

	//for through objCount and create objs
	for (int i = 0; i < objCount; i++)
	{
		int objType = 0;
		loadFile >> objType;
		switch (objType)
		{
		case GameObject::EObjType::OBJ_TYPE_DEFAULT:
		{
			VisibleObject* vis = new VisibleObject(assets);
			vis->load(loadFile);
			vis->setObjType(GameObject::EObjType::OBJ_TYPE_DEFAULT);
			addObj(vis);
		}break;
		case GameObject::EObjType::OBJ_TYPE_PLAYERSTART:
		{
			VisibleObject* vis = new VisibleObject(assets);
			vis->load(loadFile);
			assets.setPlayerStart(vis->getPosition());
		}break;
		case GameObject::EObjType::OBJ_TYPE_INTERACT:
		{
			int interType = 0;
			loadFile >> interType;
			switch (interType)
			{
			case InteractObject::EInteract::INTER_NONE:
				//should never happen
				break;
			case InteractObject::EInteract::INTER_HEALTH:
				//create health
			{
				InteractHealth* vis = new InteractHealth(assets);
				vis->load(loadFile);
				vis->setObjType(GameObject::EObjType::OBJ_TYPE_INTERACT);
				vis->setInterType(InteractObject::EInteract::INTER_HEALTH);
				addObj(vis);
			}
				break;
			case InteractObject::EInteract::INTER_KEY:
				//create key
			{
				InteractKey* vis = new InteractKey(assets);
				vis->load(loadFile);
				addObj(vis);
			}
				break;
			case InteractObject::EInteract::INTER_DOOR:
				//create door
			{
				InteractDoor* vis = new InteractDoor(assets);
				vis->load(loadFile);
				addObj(vis);
			}
				break;
			}
		}break;
		}
		
	}
}