#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML\Graphics.hpp"
class GameObject : public sf::Transformable
{
public:
	enum EObjType
	{
		OBJ_TYPE_DEFAULT = 0,
		OBJ_TYPE_PHYS = 1,
		OBJ_TYPE_PLAYERSTART = 2,
		OBJ_TYPE_INTERACT = 3,
		OBJ_PLAYER = 4
	};

	GameObject();
	void markForDeletion();
	bool wantsDelete();
	void setObjType(EObjType pType);
	EObjType getObjType();
private:
	EObjType type;
	bool shouldDelete;
};

#endif