#include "GameObject.h"

GameObject::GameObject()
{
	type = OBJ_TYPE_DEFAULT;
}

void GameObject::setObjType(EObjType pType)
{
	type = pType;
}

GameObject::EObjType GameObject::getObjType()
{
	return type;
}