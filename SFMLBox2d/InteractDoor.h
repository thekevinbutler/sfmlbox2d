#ifndef INTERACTDOOR_H
#define INTERACTDOOR_H

#include "VisibleObject.h"
#include "InteractObject.h"

class InteractDoor : public VisibleObject, public InteractObject
{
public:
	InteractDoor(AssetManager& assets);
	virtual void interact(Player* player);
	void load(std::ifstream& loadFile);

	bool update(sf::Time dt);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
private:
	std::string keyName;
	std::string nextWorldName;

};


#endif