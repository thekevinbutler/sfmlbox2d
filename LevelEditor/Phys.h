#ifndef PHYS_H
#define PHYS_H
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "SFML\Graphics.hpp"
class Phys : public GameObject, public sf::Drawable
{
public:
	enum EPhysPrim
	{
		PHYS_PRIM_LINE,
		PHYS_PRIM_TRI,
		PHYS_PRIM_QUAD
	};
	enum EPhysProperties
	{
		PHYS_PROP_DEFAULT,
		PHYS_PROP_ICE,
		PHYS_PROP_RUBBER,
		PHYS_PROP_STICKY,
		PHYS_PROP_DEATH
	};
	Phys() = delete;
	Phys(EPhysPrim primType, EPhysProperties prop);
	void setVertices(sf::VertexArray pVerts);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds();
	bool save(std::ofstream& saveFile);
private:
	EPhysPrim physPrimType;
	EPhysProperties physProp;
	sf::VertexArray verts;
	float friction;
	//sf::RectangleShape boundingRect;
};
#endif