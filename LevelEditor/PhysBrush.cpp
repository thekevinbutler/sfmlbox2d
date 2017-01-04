#include "PhysBrush.h"

PhysBrush::PhysBrush()
{
	started = false;
	menu = NULL;
}


//CANT USE WITHOUT INITIALIZING
void PhysBrush::init(PhysProperties* pMenu)
{
	menu = pMenu;
}

void PhysBrush::start()
{
	//clear in case points still exist
	physPoints.clear();
	started = true;
	currentVert = 0;
	primitive = static_cast<Phys::EPhysPrim>(menu->getPrim());
	props = static_cast<Phys::EPhysProperties>(menu->getProp());
	switch (primitive)
	{
	case Phys::EPhysPrim::PHYS_PRIM_LINE:
		totalVerts = 2;
		physPoints.setPrimitiveType(sf::Lines);
		physPoints.resize(totalVerts);
		break;
	case Phys::EPhysPrim::PHYS_PRIM_TRI:
		totalVerts = 3;
		physPoints.setPrimitiveType(sf::Triangles);
		physPoints.resize(totalVerts);
		break;
	case Phys::EPhysPrim::PHYS_PRIM_QUAD:
		totalVerts = 4;
		physPoints.setPrimitiveType(sf::Quads);
		physPoints.resize(totalVerts);
		break;
	}
}

void PhysBrush::end()
{
	started = false;
	physPoints.clear();
}

bool PhysBrush::addPoint(sf::Vector2f newPoint)
{
	//these are global coordinates!!
	physPoints[currentVert].position = newPoint;
	currentVert++;
	return currentVert != totalVerts;
}

Phys* PhysBrush::buildPhysObj()
{
	Phys* newPhys = new Phys(primitive, props);
	newPhys->setVertices(physPoints);
	return newPhys;
}