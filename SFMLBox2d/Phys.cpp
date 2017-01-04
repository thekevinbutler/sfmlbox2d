#include "Phys.h"
#include "util.h"
Phys::Phys(b2World& pWorld, EPhysPrim primType, EPhysProperties prop) : world(pWorld)
{
	physPrimType = primType;
	physProp = prop;
}
Phys::~Phys()
{
	world.DestroyBody(body);
}

void Phys::setVertices(sf::VertexArray pVerts)
{
	verts = pVerts;
	setPosition(0, 0);
	setColor();
}
void Phys::setColor()
{
	for (int i = 0; i < verts.getVertexCount(); i++)
	{
		switch (physProp)
		{
		case PHYS_PROP_DEFAULT:
			verts[i].color = sf::Color(255, 255, 255, 128);
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
void Phys::load(std::ifstream& loadFile)
{
	//copy exact format from save!!!
	//load primitive type
	int prim = 0;
	loadFile >> prim;
	physPrimType = (EPhysPrim)prim;
	
	//load property type
	int prop = 0;
	loadFile >> prop;
	physProp = (EPhysProperties)prop;
	
	//load vertex count
	int vertCount = 0;
	loadFile >> vertCount;
	
	//clear preexisting vertices if any then set primitive type for vertexarray
	verts.clear();
	switch (physPrimType)
	{
	case PHYS_PRIM_LINE:
	{
		verts.setPrimitiveType(sf::Lines);
		verts.resize(2);
	}break;
	case PHYS_PRIM_TRI:
	{
		verts.setPrimitiveType(sf::Triangles);
		verts.resize(3);
	}break;
	case PHYS_PRIM_QUAD:
	{
		verts.setPrimitiveType(sf::Quads);
		verts.resize(4);
	}break;
	}

	//load position of each vertex
	for (int i = 0; i < vertCount; i++)
	{
		sf::Vector2f pos;
		loadFile >> pos.x >> pos.y;
		verts[i].position = pos;
	}

	//since transformable, load position of transform
	sf::Vector2f transPos;
	loadFile >> transPos.x >> transPos.y;
	setPosition(transPos);

	//load rotation
	float rot = 0.0f;
	loadFile >> rot;
	setRotation(rot);

	//load scale x and y
	sf::Vector2f transScale;
	loadFile >> transScale.x >> transScale.y;
	setScale(transScale);

	//loaded
	createPhys();
	setColor();
}
void Phys::createPhys()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(convert::pixelsToMeters<double>(getPosition().x),
		convert::pixelsToMeters<double>(getPosition().y));
	bodyDef.type = b2_staticBody;

	//turn vertexArray into b2vec2 array

	
	b2PolygonShape b2shape;
	b2EdgeShape b2Edge;
	switch (physPrimType)
	{
	case PHYS_PRIM_LINE:
	{
		b2Vec2 b2line[2];
		for (int i = 0; i < verts.getVertexCount(); i++)
		{
			b2line[i] = b2Vec2(convert::pixelsToMeters<double>(verts[i].position.x),
				convert::pixelsToMeters<double>(verts[i].position.y));
		}
		b2Edge.Set(b2line[0], b2line[1]);
	}break;
	case PHYS_PRIM_TRI:
	{
		b2Vec2 b2tri[3];
		for (int i = 0; i < verts.getVertexCount(); i++)
		{
			b2tri[i] = b2Vec2(convert::pixelsToMeters<double>(verts[i].position.x),
				convert::pixelsToMeters<double>(verts[i].position.y));
		}
		b2shape.Set(b2tri, 3);
	}break;
	case PHYS_PRIM_QUAD:
	{
		b2Vec2 b2quad[4];
		for (int i = 0; i < verts.getVertexCount(); i++)
		{
			b2quad[i] = b2Vec2(convert::pixelsToMeters<double>(verts[i].position.x),
				convert::pixelsToMeters<double>(verts[i].position.y));
		}
		b2shape.Set(b2quad, 4);
	}break;
	}
	

	b2FixtureDef fixtureDef;
	switch (physProp)
	{
	case PHYS_PROP_DEFAULT:
		fixtureDef.friction = 0.03;
		fixtureDef.restitution = 0.0;
		break;
	case PHYS_PROP_ICE:
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 0.0;
		break;
	case PHYS_PROP_RUBBER:
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		break;
	case PHYS_PROP_STICKY:
		fixtureDef.friction = 0.1;
		fixtureDef.restitution = 0.0;
		break;
	case PHYS_PROP_DEATH:
		fixtureDef.friction = 1.0;
		fixtureDef.restitution = 0.0;
		break;
	}
	fixtureDef.density = 1.0;
	if (physPrimType == PHYS_PRIM_LINE)
	{
		fixtureDef.shape = &b2Edge;
	}
	else
	{
		fixtureDef.shape = &b2shape;
	}
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	body->SetUserData(this);

}

