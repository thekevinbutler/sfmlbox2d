#include "VisibleObject.h"

VisibleObject::VisibleObject(AssetManager& pAssets) : assets(pAssets)
{

}

void VisibleObject::setTexture(sf::Texture* pTex, std::string texName)
{
	textureName = texName;

	tex = *pTex;
	verts.setPrimitiveType(sf::Quads);
	verts.resize(4);

	verts[0].position = sf::Vector2f(0.0f, 0.0f);
	verts[1].position = sf::Vector2f(tex.getSize().x, 0.0f);
	verts[2].position = sf::Vector2f(tex.getSize());
	verts[3].position = sf::Vector2f(0.0f, tex.getSize().y);

	verts[0].texCoords = sf::Vector2f(0, 0);
	verts[1].texCoords = sf::Vector2f(tex.getSize().x, 0.0f);
	verts[2].texCoords = sf::Vector2f(tex.getSize());
	verts[3].texCoords = sf::Vector2f(0, tex.getSize().y);
	
	//since origin defaults to 0,0 and vert[0] is 0,0 it is topleft justified. Center it to middle
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

bool VisibleObject::update(sf::Time dt)
{
	return !wantsDelete(); //if returns false, it will get deleted so return not wants delete
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
	//sf::FloatRect rect(verts[0].position, sf::Vector2f(verts[2].position.x - verts[0].position.x, verts[2].position.y - verts[0].position.y)); i might need to see this version of rect... who knows
	sf::FloatRect rect(0, 0, tex.getSize().x, tex.getSize().y);
	return getTransform().transformRect(rect);
}
sf::Vector2f VisibleObject::getSizeScaled()
{
	sf::Vector2f scaled;
	scaled.x = tex.getSize().x * getScale().x;
	scaled.y = tex.getSize().y * getScale().y;

	return scaled;
}
bool VisibleObject::save(std::ofstream& saveFile)
{
	//save object type first
	saveFile << getObjType() << "\n";

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

void VisibleObject::load(std::ifstream& loadFile)
{
	//PULLING THIS! will set the object type in layer since i need this data to switch between VObjs
	////load object type
	//int objType = 0;
	//loadFile >> objType;
	//setObjType((GameObject::EObjType)objType);

	//load Texture name
	std::string name;
	loadFile >> name;
	textureName = name;
	setTexture(assets.getTexture(textureName),textureName);

	//load position of transform
	sf::Vector2f pos;
	loadFile >> pos.x >> pos.y;
	setPosition(pos);

	//load rotation of transform
	float rot = 0.0f;
	loadFile >> rot;
	setRotation(rot);

	//load scale of x and y
	sf::Vector2f transScale;
	loadFile >> transScale.x >> transScale.y;
	setScale(transScale);

	//loaded
}