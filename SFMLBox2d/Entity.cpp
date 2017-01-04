#include "Entity.h"

Entity::Entity()
{
	type = EDEFAULT;
}
Entity::Entity(EType eType)
{
	type = eType;
}
Entity::EType Entity::getType()
{
	return type;
}