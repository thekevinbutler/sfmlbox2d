#include "InteactHealth.h"
float elapsedTime = 0.0f;
InteractHealth::InteractHealth(AssetManager& pAssets) : VisibleObject(pAssets), InteractObject(pAssets.getPhysWorld())
{}
void InteractHealth::interact(Player* player)
{
	player->affectHealth(100);
	markForDeletion();
}
bool InteractHealth::update(sf::Time dt)
{
	elapsedTime += dt.asSeconds();
	setPosition(initialPos.x, initialPos.y - abs(sin(elapsedTime* 2.0)*10.0f));
	halo.setPosition(getPosition());
	halo.rotate(dt.asSeconds()*360.0f);
	return !wantsDelete();
}
void InteractHealth::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	render.draw(halo);
	VisibleObject::draw(render, states);
}
void InteractHealth::load(std::ifstream& loadFile)
{
	VisibleObject::load(loadFile);
	setObjType(GameObject::EObjType::OBJ_TYPE_INTERACT);
	setInterType(InteractObject::EInteract::INTER_HEALTH);
	createPhys(getAssets().getPhysWorld(), getPosition().x, getPosition().y, getSizeScaled().x, getSizeScaled().y, this);
	initialPos = getPosition();
	//DEBUG
	haloTex = getAssets().getTexture("no.png");
	halo.setTexture(*haloTex, true);
	halo.setPosition(initialPos);
	halo.setOrigin(haloTex->getSize().x / 2.0, haloTex->getSize().y / 2.0);
	halo.setColor(sf::Color(255, 255, 255, 128));
	halo.scale(0.5,0.5);
}