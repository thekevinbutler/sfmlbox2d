#include "Phys.h"

Phys::Phys(EPhysPrim primType, EPhysProperties prop)
{
	physPrimType = primType;
	physProp = prop;
}

void Phys::setVertices(sf::VertexArray pVerts)
{
	verts = pVerts;
	setPosition(0, 0);
	for (int i = 0; i < verts.getVertexCount(); i++)
	{
		switch (physProp)
		{
		case PHYS_PROP_DEFAULT:
			verts[i].color = sf::Color(255,255,255,128);
			break;
		case PHYS_PROP_ICE:
			verts[i].color = sf::Color(0, 0, 255, 128);
			break;
		case PHYS_PROP_RUBBER:
			verts[i].color = sf::Color(255, 0, 255, 128);
			break;
		case PHYS_PROP_STICKY:
			verts[i].color = sf::Color(255, 255, 0, 128);
			break;
		case PHYS_PROP_DEATH:
			verts[i].color = sf::Color(255, 0, 0, 128);
			break;
		}
		
	}
}

void Phys::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	//states.texture = &tex;

	// you may also override states.shader or states.blendMode if you want
	
	// draw the vertex array
	render.draw(verts, states);
}

sf::FloatRect Phys::getGlobalBounds()
{
	sf::FloatRect rect;
	switch (physPrimType)
	{
	case PHYS_PRIM_LINE:
		rect.top = 0.0f;
		rect.width = abs(verts[0].position.x - verts[1].position.x);
		rect.height = abs(verts[0].position.y - verts[1].position.y);
		rect.left = 0.0f;
		break;
	case PHYS_PRIM_TRI:
		rect.top = 0.0f;
		rect.width = abs(verts[0].position.x - verts[1].position.x);
		rect.height = abs(verts[0].position.y - verts[2].position.y);
		rect.left = 0.0f;
		break;
	case PHYS_PRIM_QUAD:
		rect.top = 0.0f;
		rect.width = abs(verts[0].position.x - verts[2].position.x);
		rect.height = abs(verts[0].position.y - verts[2].position.y);
		rect.left = 0.0f;
		break;
	}
	//sf::FloatRect rect(verts[0].position, sf::Vector2f(verts[2].position.x - verts[0].position.x, verts[2].position.y - verts[0].position.y));
	//sf::FloatRect rect(0, 0, tex.getSize().x, tex.getSize().y);
	return getTransform().transformRect(rect);
}

bool Phys::save(std::ofstream& saveFile)
{
	//save primitive first
	saveFile << physPrimType << "\n";

	//save physProperties
	saveFile << physProp << "\n";

	//save vertex count
	saveFile << verts.getVertexCount() << "\n";

	//for through vertex array and save each position
	for (int i = 0; i < verts.getVertexCount(); i++)
	{
		//save position of Ith vertex
		saveFile << verts[i].position.x << " " << verts[i].position.y << "\n";
		//dont need color or texCoords since they are assigned by type of property
	}
	//since transformable, save that data
	saveFile << getPosition().x << " " << getPosition().y << "\n";

	//save rotation
	saveFile << getRotation() << "\n";

	//save scale
	saveFile << getScale().x << " " << getScale().y << "\n";

	return true;
}