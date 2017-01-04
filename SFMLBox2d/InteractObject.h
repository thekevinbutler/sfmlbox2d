#ifndef INTERACTOBJECT_H
#define INTERACTOBJECT_H

#include "Box2D\Box2D.h"
#include "Player.h"

class InteractObject
{
public:
	enum EInteract
	{
		INTER_NONE,
		INTER_HEALTH,
		INTER_KEY, //key must be same name as door
		INTER_DOOR, //if door has name, then locked, else always unlocked

	};
	InteractObject(b2World& pWorld);
	~InteractObject();
	virtual void interact(Player* player) = 0;
	void createPhys(b2World& world, float posx, float posy, float sizex, float sizey, void* pGameObj);
	void setInterType(int newInter){ interType = (EInteract)newInter; }
	int getInterType(){ return interType; }
private:
	b2World& world;
	b2Body* body;
	EInteract interType;
};

#endif