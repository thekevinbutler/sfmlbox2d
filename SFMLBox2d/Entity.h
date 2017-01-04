#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	enum EType
	{
		EDEFAULT,
		EPLAYER,
		EGROUND
	};
	EType getType();
	Entity();
	Entity(EType eType);
private:
	EType type;
};

#endif