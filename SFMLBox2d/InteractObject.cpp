#include "InteractObject.h"
#include "util.h"
InteractObject::InteractObject(b2World& pWorld) : world(pWorld)
{
	
}
InteractObject::~InteractObject()
{
	world.DestroyBody(body);
}
void InteractObject::createPhys(b2World& world, float posx, float posy, float sizex, float sizey, void* pGameObj)
{
	//Body definition like type and position
	b2BodyDef bodyDef;
	bodyDef.position.Set(convert::pixelsToMeters<double>(posx),
		convert::pixelsToMeters<double>(posy));
	bodyDef.type = b2_staticBody;

	//shape of the body
	b2PolygonShape b2shape;
	b2shape.SetAsBox(convert::pixelsToMeters<double>(sizex / 2.0),
		convert::pixelsToMeters<double>(sizey / 2.0));

	b2FixtureDef sensorDef;
	sensorDef.isSensor = true;
	sensorDef.shape = &b2shape;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&sensorDef);

	body->SetUserData(pGameObj);
}