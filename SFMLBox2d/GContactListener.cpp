#include "GContactListener.h"
#include "Player.h"
#include "InteactHealth.h"
#include "VisibleObject.h"

InteractObject* gInterObj = NULL;
Player* gPlayer = NULL;

GContactListener::GContactListener()
{

}
void GContactListener::BeginContact(b2Contact* contact)
{
	contacts = contact;
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	if (!playerBeginContact(fixA, fixB))
	{
		playerBeginContact(fixB, fixA);
	}

	GameObject* objA = NULL;
	GameObject* objB = NULL;

	void* bodyUserData = fixA->GetBody()->GetUserData();
	if (bodyUserData)
	{
		objA = static_cast<GameObject*>(fixA->GetBody()->GetUserData());
	}
	bodyUserData = fixB->GetBody()->GetUserData();
	if (bodyUserData)
	{
		objB = static_cast<GameObject*>(fixB->GetBody()->GetUserData());
	}
	//////check if fixture A was the foot sensor
	if (objA)
	{
		if (objA->getObjType() == GameObject::EObjType::OBJ_PLAYER)
		{
			//Player* player = dynamic_cast<Player*>(objA);
			////test health
			//bool fixtureB = contact->GetFixtureB()->IsSensor();
			//if (fixtureB)
			//{
			//	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			//	GameObject* gObj = static_cast<GameObject*>(bodyUserDataB);
			//	if (gObj->getObjType() == GameObject::EObjType::OBJ_TYPE_INTERACT)
			//	{
			//		InteractHealth* obj = dynamic_cast<InteractHealth*>(gObj);
			//		if (obj->getInterType() == InteractObject::EInteract::INTER_HEALTH)
			//		{
			//			obj->interact(player);
			//		}
			//	}
			//	
			//	
			//}

			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if ((int)fixtureUserData == 3)
			numContacts++;

		}
			
	}
	//check if fixture B was the foot sensor
	//bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (objB)
	{
		GameObject::EObjType res = static_cast<GameObject*>(bodyUserData)->getObjType();
		if (res == GameObject::EObjType::OBJ_PLAYER)
		{
			//Player* player = dynamic_cast<Player*>(objB);
			////test health
			//bool fixtureA = contact->GetFixtureA()->IsSensor();
			//if (fixtureA)
			//{
			//	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			//	InteractObject* obj = static_cast<InteractObject*>(bodyUserDataA);
			//	if (obj->getInterType() == InteractObject::EInteract::INTER_HEALTH)
			//	{
			//		obj->interact(player);
			//	}
			//}

			void* fixtureUserData = contact->GetFixtureB()->GetUserData();
			if ((int)fixtureUserData == 3)
				numContacts++;
		}
	}
	/*void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		numContacts++;
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
		numContacts++;*/
}

void GContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	if (!playerEndContact(fixA, fixB))
	{
		playerEndContact(fixB, fixA);
	}

	////check if fixture A was the foot sensor
	//void* fixtureUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	//if (fixtureUserData)
	//{
	//	GameObject::EObjType res = static_cast<Player*>(fixtureUserData)->getType();
	//	if (res == GameObject::EObjType::EPLAYER)
	//		numContacts--;
	//}
	////check if fixture B was the foot sensor
	//fixtureUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	//if (fixtureUserData)
	//{
	//	GameObject::EObjType res = static_cast<Player*>(fixtureUserData)->getType();
	//	if (res == GameObject::EObjType::EPLAYER)
	//		numContacts--;
	//}
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		numContacts--;
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
		numContacts--;
}
bool GContactListener::playerBeginContact(b2Fixture* playerFix, b2Fixture* worldFix)
{
	GameObject* obj1 = static_cast<GameObject*>(playerFix->GetBody()->GetUserData());
	
	if (obj1->getObjType() == GameObject::EObjType::OBJ_PLAYER)
	{
		Player* player = dynamic_cast<Player*>(obj1);
		if (player)
		{
			gPlayer = player;
		}
		GameObject* obj2 = static_cast<GameObject*>(worldFix->GetBody()->GetUserData());
		if (obj2->getObjType() == GameObject::EObjType::OBJ_TYPE_INTERACT)
		{
			InteractObject* interObj = dynamic_cast<InteractObject*>(obj2);
			if (interObj)
			{
				gInterObj = interObj;
			}
		}
		return true;
	}
	return false;
}

bool GContactListener::playerEndContact(b2Fixture* playerFix, b2Fixture* worldFix)
{
	GameObject* obj1 = static_cast<GameObject*>(playerFix->GetBody()->GetUserData());

	if (obj1->getObjType() == GameObject::EObjType::OBJ_PLAYER)
	{
		Player* player = dynamic_cast<Player*>(obj1);
		if (player)
		{
			gPlayer = NULL;
		}
		GameObject* obj2 = static_cast<GameObject*>(worldFix->GetBody()->GetUserData());
		if (obj2->getObjType() == GameObject::EObjType::OBJ_TYPE_INTERACT)
		{
			InteractObject* interObj = dynamic_cast<InteractObject*>(obj2);
			if (interObj)
			{
				gInterObj = NULL;
			}
		}
		return true;
	}
	return false;
}

void GContactListener::interact()
{
	//if object exists
	if (gInterObj && gPlayer)
	{
		gInterObj->interact(gPlayer);
	}
}