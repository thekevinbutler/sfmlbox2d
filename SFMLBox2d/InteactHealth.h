#ifndef INTERACTHEALTH_H
#define INTERACTHEALTH_H

#include "VisibleObject.h"
#include "InteractObject.h"

class InteractHealth : public VisibleObject, public InteractObject
{
public:
	InteractHealth(AssetManager& assets);
	virtual void interact(Player* player);
	void load(std::ifstream& loadFile);

	bool update(sf::Time dt);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
private:
	sf::Vector2f initialPos;
	sf::Texture* haloTex;
	sf::Sprite halo;
};

#endif