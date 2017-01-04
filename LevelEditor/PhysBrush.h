#ifndef PHYSBRUSH_H
#define PHYSBRUSH_H

#include "PhysProperties.h"
#include "Phys.h"
#include "SFML\Graphics.hpp"

class PhysBrush
{
public:
	PhysBrush();
	void init(PhysProperties* pMenu);
	//call to start adding points
	void start();
	void end();
	//returns true if still needs more points to fulfill primitive
	//once false, make sure to call buildPhysObj
	bool addPoint(sf::Vector2f newPoint);

	//builds phys object on the heap and returns pointer for storage
	Phys* buildPhysObj();
private:
	bool started;
	int totalVerts;
	int currentVert;
	PhysProperties* menu;
	sf::VertexArray physPoints;
	Phys::EPhysPrim primitive;
	Phys::EPhysProperties props;
};


#endif