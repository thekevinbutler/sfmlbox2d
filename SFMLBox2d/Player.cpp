#include "Player.h"
#include "Game.h"
#include "util.h"
#include <iostream>

Player::Player(b2World& world)
{
	changeWorld = false;
	setObjType(GameObject::EObjType::OBJ_PLAYER);
	//contact listener -- listens for player to hit object
	world.SetContactListener(&physListener);
	//set speeds
	speedMax = 3.0f;
	speedWalking = 0.01f;
	speedRunning = 0.02f;
	
	//controls
	bind(Action(sf::Keyboard::A), [this](const sf::Event&)
	{
		if (isGrounded())
		{
			if (phys->GetLinearVelocity().x > -speedMax)
			{
				phys->ApplyLinearImpulse(b2Vec2(running ? -speedRunning : -speedWalking, 0.0f), phys->GetPosition(), true);
			}
		}
		else
		{
			if (phys->GetLinearVelocity().x > -speedMax)
			{
				phys->ApplyLinearImpulse(b2Vec2(running ? -speedRunning : -speedWalking, 0.0f), phys->GetPosition(), true);
			}

		}
	});
	bind(Action(sf::Keyboard::D), [this](const sf::Event&)
	{
		if (isGrounded())
		{
			if (phys->GetLinearVelocity().x < speedMax)
				phys->ApplyLinearImpulse(b2Vec2(running ? speedRunning : speedWalking, 0.0f), phys->GetPosition(), true);
		}
		else
		{
			if (phys->GetLinearVelocity().x < speedMax)
				phys->ApplyLinearImpulse(b2Vec2(running ? speedRunning : speedWalking, 0.0f), phys->GetPosition(), true);
		}
	});
	bind(Action(sf::Keyboard::Space, Action::Type::Pressed), [this](const sf::Event&)
	{
		if (isGrounded())
		{
			phys->ApplyLinearImpulse(b2Vec2(0.0f, -0.35f), phys->GetPosition(), true);
		}
	});
	bind(Action(sf::Keyboard::E, Action::Type::Pressed), [this](const sf::Event&)
	{
		physListener.interact();
	});
	bind(Action(sf::Keyboard::W), [this](const sf::Event&)
	{
		phys->ApplyForce(b2Vec2(0.0f, -6.0f), phys->GetPosition(), true);
	});
	bind(Action(sf::Keyboard::LShift), [this](const sf::Event&)
	{
		running = true;
		speedMax = 6.0;
	});
	bind(Action(sf::Keyboard::LShift, Action::Released), [this](const sf::Event&)
	{
		running = false;
		speedMax = 3.0;
	});
	sf::Vector2f initialPos(0.0f, 0.0f);
	running = false;
	health = 50;


	//load texture for player
	tex.loadFromFile("player.png");
	//set texture to sprite
	sprite.setTexture(tex);
	sprite.setOrigin(tex.getSize().x / 2.0f, tex.getSize().y / 2.0f);
	sprite.setPosition(initialPos);

	//moved physics creation to own function
	phys = createPhys(world, initialPos.x, initialPos.y, 32, 32);
}
void Player::setStartPos(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
	phys->SetTransform(b2Vec2(convert::pixelsToMeters<double>(newPos.x),
		convert::pixelsToMeters<double>(newPos.y)),phys->GetAngle());
}

b2Body* Player::createPhys(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(convert::pixelsToMeters<double>(pos_x),
		convert::pixelsToMeters<double>(pos_y));
	bodyDef.type = type;

	b2PolygonShape b2shape;
	b2shape.SetAsBox(convert::pixelsToMeters<double>(size_x / 2.0),
		convert::pixelsToMeters<double>(size_y / 2.0));

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 10.0;
	fixtureDef.restitution = 0.0;
	fixtureDef.shape = &b2shape;



	b2PolygonShape foot;
	foot.SetAsBox(convert::pixelsToMeters<double>(size_x / 4.0),
		convert::pixelsToMeters<double>(size_y / 4.0),
		b2Vec2(0, convert::pixelsToMeters<double>(size_y / 2.0)), 0);
	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	footFixtureDef.shape = &foot;
	

	b2Body* res = world.CreateBody(&bodyDef);
	res->CreateFixture(&fixtureDef);
	res->SetFixedRotation(true);

	b2Fixture* footSensorFixture = res->CreateFixture(&footFixtureDef);
	footSensorFixture->SetUserData((void*)3);

	res->SetUserData(this);
	return res;
}

void Player::processEvents()
{
	ActionTarget::processEvents();
}

bool Player::update(sf::Time dt)
{
	if (changeWorld)
	{
		return false;
	}
	sprite.setPosition(getPos());
	return true;
}
void Player::draw(b2World& world, sf::RenderWindow& window)
{
	window.draw(sprite);
}


sf::Vector2f Player::getPos()
{
	return sf::Vector2f(convert::metersToPixels<float>(phys->GetPosition().x), convert::metersToPixels<float>(phys->GetPosition().y));
}

bool Player::isGrounded()
{
	return physListener.getContacts() > 0;
}

//points can be negative or positive
void Player::affectHealth(int points)
{
	health += points;
	health = b2Clamp<int>(health, 0, 100);
}

int Player::getHealth()
{
	return health;
}

void Player::addKey(std::string name)
{
	std::pair<std::string, bool> key(name, true);
	keys.insert(key);
}

bool Player::useKey(std::string name)
{
	std::map<std::string,bool>::iterator results = keys.find(name);
	if (keys.end() == results)
	{
		return false;
	}
	results->second = false;
	return true;
}

void Player::setNextWorld(std::string name)
{
	nextWorld = name;
	changeWorld = true;
}

std::string Player::getNextWorld()
{
	changeWorld = false;
	curWorld = nextWorld;
	nextWorld = "";
	return curWorld;
}
std::string Player::sendDebug()
{
	float x = phys->GetLinearVelocity().x;
	std::string res;
	res = "X: " + std::to_string(phys->GetLinearVelocity().x) + '\n' +
		"Y: " + std::to_string(phys->GetLinearVelocity().y) + '\n' +
		"length: " + std::to_string(phys->GetLinearVelocity().Length());

	return res;
}