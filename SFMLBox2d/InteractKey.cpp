#include "InteractKey.h"

InteractKey::InteractKey(AssetManager& pAssets) : VisibleObject(pAssets), InteractObject(pAssets.getPhysWorld())
{
	elapsedTime = 0.0f;
}
void InteractKey::interact(Player* player)
{
	player->addKey(keyName);
	markForDeletion();
}
bool InteractKey::update(sf::Time dt)
{
	elapsedTime += dt.asSeconds();
	setPosition(initialPos.x, initialPos.y - abs(sin(elapsedTime* 2.0)*10.0f));
	halo.setPosition(getPosition());
	halo.rotate(dt.asSeconds()*360.0f);
	return !wantsDelete();
}
void InteractKey::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	render.draw(halo);
	VisibleObject::draw(render, states);
}
void InteractKey::load(std::ifstream& loadFile)
{
	//load Key name
	loadFile >> keyName;

	VisibleObject::load(loadFile);
	setObjType(GameObject::EObjType::OBJ_TYPE_INTERACT);
	setInterType(InteractObject::EInteract::INTER_KEY);
	createPhys(getAssets().getPhysWorld(), getPosition().x, getPosition().y, getSizeScaled().x, getSizeScaled().y, this);
	initialPos = getPosition();
	scale(0.5, 0.5);
	//DEBUG
	haloTex = getAssets().getTexture("no.png");
	halo.setTexture(*haloTex, true);
	halo.setPosition(initialPos);
	halo.setOrigin(haloTex->getSize().x / 2.0, haloTex->getSize().y / 2.0);
	halo.setColor(sf::Color(255, 255, 255, 128));
	halo.scale(0.5, 0.5);
}