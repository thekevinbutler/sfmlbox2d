#ifndef INTERACTKEY_H
#define INTERACTKEY_H

#include "VisibleObject.h"
#include "InteractObject.h"

class InteractKey : public VisibleObject, public InteractObject
{
public:
	InteractKey(AssetManager& assets);
	virtual void interact(Player* player);
	void load(std::ifstream& loadFile);

	bool update(sf::Time dt);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
private:
	float elapsedTime;
	std::string keyName;
	sf::Vector2f initialPos;
	sf::Texture* haloTex;
	sf::Sprite halo;

};

#endif