#include "GameObject.h"

GameObject::GameObject()
{
	type = OBJ_TYPE_DEFAULT;
	shouldDelete = false;
}

void GameObject::setObjType(EObjType pType)
{
	type = pType;
}

GameObject::EObjType GameObject::getObjType()
{
	return type;
}

void GameObject::markForDeletion()
{
	shouldDelete = true;
}
bool GameObject::wantsDelete()
{
	return shouldDelete;
}