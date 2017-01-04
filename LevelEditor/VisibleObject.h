#ifndef VISIBLEOBJECT_H
#define VISIBLEOBJECT_H

#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include <iostream>
#include <fstream>

class VisibleObject : public sf::Drawable, public GameObject
{
public:
	enum EInteract
	{
		INTER_NONE,
		INTER_HEALTH,
		INTER_KEY, //key must be same name as door
		INTER_DOOR, //if door has name, then locked, else always unlocked

	};

	VisibleObject();

	void setInterType(int newInter){ interType = (EInteract)newInter; }
	int getInterType(){ return interType; }
	void setOptName(std::string newName){ optName = newName; }
	std::string getOptName(){ return optName; }
	void setOptNextWorld(std::string newName){ optNextWorld = newName; }
	std::string getOptNextWorld(){ return optNextWorld; }

	//use set texture
	void setTexture(sf::Texture* pTex, std::string texName);
	bool occupiesPos(sf::Vector2f pos);
	//bool shouldDraw(sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds();
	bool save(std::ofstream& saveFile);
private:
	EInteract interType;
	sf::Texture tex;
	std::string textureName;
	std::string optName;
	std::string optNextWorld;
	sf::VertexArray verts;
};


#endif
