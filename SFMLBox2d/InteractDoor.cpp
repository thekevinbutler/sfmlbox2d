#include "InteractDoor.h"

InteractDoor::InteractDoor(AssetManager& pAssets) : VisibleObject(pAssets), InteractObject(pAssets.getPhysWorld())
{
}
void InteractDoor::interact(Player* player)
{
	if (player->useKey(keyName))
	{
		player->setNextWorld(nextWorldName);
		//markForDeletion();
	}
}
bool InteractDoor::update(sf::Time dt)
{
	return !wantsDelete();
}
void InteractDoor::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	VisibleObject::draw(render, states);
}
void InteractDoor::load(std::ifstream& loadFile)
{
	//load Key name
	loadFile >> keyName;
	loadFile >> nextWorldName;
	VisibleObject::load(loadFile);
	setObjType(GameObject::EObjType::OBJ_TYPE_INTERACT);
	setInterType(InteractObject::EInteract::INTER_DOOR);
	createPhys(getAssets().getPhysWorld(), getPosition().x, getPosition().y, getSizeScaled().x, getSizeScaled().y, this);
}