#include "VisibleObject.h"

VisibleObject::VisibleObject()
{

}

void VisibleObject::setTexture(sf::Texture* pTex, std::string texName)
{
	textureName = texName;
	/*Sprite::setTexture(*pTex, true);
	setOrigin(pTex->getSize().x / 2.0, pTex->getSize().y / 2.0);*/
	tex = *pTex;
	verts.setPrimitiveType(sf::Quads);
	verts.resize(4);
	/*verts[0].position.x = getPosition().x - (tex.getSize().x / 2);
	verts[1].position.x = getPosition().x + (tex.getSize().x / 2);
	verts[2].position.x = getPosition().x + (tex.getSize().x / 2);
	verts[3].position.x = getPosition().x - (tex.getSize().x / 2);

	verts[0].position.y = getPosition().y - (tex.getSize().y / 2);
	verts[1].position.y = getPosition().y - (tex.getSize().y / 2);
	verts[2].position.y = getPosition().y + (tex.getSize().y / 2);
	verts[3].position.y = getPosition().y + (tex.getSize().y / 2);*/

	verts[0].position = sf::Vector2f(0, 0);
	verts[1].position = sf::Vector2f(tex.getSize().x, 0);
	verts[2].position = sf::Vector2f(tex.getSize());
	verts[3].position = sf::Vector2f(0, tex.getSize().y);

	verts[0].texCoords = sf::Vector2f(0, 0);
	verts[1].texCoords = sf::Vector2f(tex.getSize().x, 0);
	verts[2].texCoords = sf::Vector2f(tex.getSize());
	verts[3].texCoords = sf::Vector2f(0, tex.getSize().y);
	setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
}
bool VisibleObject::occupiesPos(sf::Vector2f pos)
{
	if (getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}

void VisibleObject::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &tex;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	render.draw(verts, states);
}

sf::FloatRect VisibleObject::getGlobalBounds()
{
	//sf::FloatRect rect(verts[0].position, sf::Vector2f(verts[2].position.x - verts[0].position.x, verts[2].position.y - verts[0].position.y));
	sf::FloatRect rect(0, 0, tex.getSize().x, tex.getSize().y);
	return getTransform().transformRect(rect);
}

bool VisibleObject::save(std::ofstream& saveFile)
{
	//save object type first
	saveFile << getObjType() << "\n";
	//IMMEDIATELY save next type
	switch (getObjType())
	{
	case OBJ_TYPE_DEFAULT:
		//nothing for now?
		break;
	case OBJ_TYPE_PHYS:
		//nothing yet, this is for dynamic sprite physics
		break;
	case OBJ_TYPE_PLAYERSTART:
		//nothing. save as is since all it is is a position
		break;
	case OBJ_INTERACT:
	{
		//save interaction type
		saveFile << interType << "\n";
		switch (interType)
		{
		case INTER_DOOR:
			saveFile << optName << "\n";
			saveFile << optNextWorld << "\n";
			break;
		case INTER_KEY:
			saveFile << optName << "\n";
		}
	}break;


	}

	//save texture name
	saveFile << textureName << "\n";

	//save position of transform
	saveFile << getPosition().x << " " << getPosition().y << "\n";

	//save rotation of transform
	saveFile << getRotation() << "\n";

	//save scale of transform
	saveFile << getScale().x << " " << getScale().y << "\n";

	

	return true;

}