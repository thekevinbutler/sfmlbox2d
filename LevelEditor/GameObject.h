#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML\Graphics.hpp"
class GameObject : public sf::Transformable
{
public:
	enum EObjType
	{
		OBJ_TYPE_DEFAULT,
		OBJ_TYPE_PHYS,
		OBJ_TYPE_PLAYERSTART,
		OBJ_INTERACT
	};

	

	GameObject();

	void setObjType(EObjType pType);
	EObjType getObjType();
private:
	EObjType type;
};

#endif