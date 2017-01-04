#include "ObjectBrush.h"

ObjectBrush::ObjectBrush()
{
	assets = NULL;
	curTex = NULL;
}

void ObjectBrush::init(AssetManager* pAssets)
{
	assets = pAssets;
}

sf::Sprite& ObjectBrush::draw(sf::Vector2f pos)
{
	brushOverlay.setPosition(pos);
	brushOverlay.setColor(sf::Color(255, 255, 255, 128));
	return brushOverlay;
}

VisibleObject* ObjectBrush::addCurObject()
{
	if (curTex)
	{
		VisibleObject* obj = new VisibleObject();
		obj->setTexture(curTex, texName);
		return obj;
	}
	return NULL;
}

bool ObjectBrush::setActiveBrush(std::string name)
{
	if (name != "")
	{
		texName = name;
		curTex = assets->getTexture(name);
		brushOverlay.setTexture(*curTex, true);
		brushOverlay.setOrigin(curTex->getSize().x / 2.0f, curTex->getSize().y / 2.0f);
		return true;
	}
	return false;
}