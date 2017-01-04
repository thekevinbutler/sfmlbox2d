#ifndef PHYS_H
#define PHYS_H
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
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
	Phys(b2World& pWorld, EPhysPrim primType, EPhysProperties prop);
	~Phys();
	void setVertices(sf::VertexArray pVerts);
	void load(std::ifstream& loadFile);
	void setColor();

	//call after either setVertices or load
	void createPhys();

	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds();
	bool save(std::ofstream& saveFile);
private:
	b2World& world;
	b2Body* body;
	EPhysPrim physPrimType;
	EPhysProperties physProp;
	sf::VertexArray verts;
	
	//sf::RectangleShape boundingRect;
};
#endif