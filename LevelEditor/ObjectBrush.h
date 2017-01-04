#ifndef OBJECTBRUSH_H
#define OBJECTBRUSH

#include "AssetManager.h"
#include "SFML\Graphics.hpp"
#include "VisibleObject.h"
class ObjectBrush
{
public:
	ObjectBrush();
	void init(AssetManager* pAssets);
	sf::Sprite& draw(sf::Vector2f pos);
	bool setActiveBrush(std::string name);
	VisibleObject* addCurObject();
private:
	sf::Sprite brushOverlay;
	AssetManager* assets;
	sf::Texture* curTex;
	std::string texName;
};

#endif
