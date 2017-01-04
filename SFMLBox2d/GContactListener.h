#ifndef GCONTACTLISTENER_H
#define GCONTACTLISTENER_H

#include "Box2D\Box2D.h"
#include "GameObject.h"
class GContactListener : public b2ContactListener
{
public:
	GContactListener();
	int getContacts(){ return numContacts; }
	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);
	void interact();
	bool playerBeginContact(b2Fixture* playerFix, b2Fixture* worldFix);
	bool playerEndContact(b2Fixture* playerFix, b2Fixture* worldFix);
private:
	b2Contact* contacts;
	int numContacts;
};

#endif