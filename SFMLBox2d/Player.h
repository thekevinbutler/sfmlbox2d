#ifndef PLAYER_H
#define PLAYER_H
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "ActionTarget.h"
#include "GContactListener.h"
#include <map>

class Player : public ActionTarget , public GameObject
{
public:

	Player(b2World& world);

	bool update(sf::Time dt);
	
	void processEvents();

	void draw(b2World& world, sf::RenderWindow& window);
	
	sf::Vector2f getPos();
	bool isGrounded();
	std::string sendDebug();
	void setStartPos(sf::Vector2f newPos);
	void affectHealth(int points);
	int getHealth();
	void addKey(std::string name);
	//use key returns true if used or false if doesn't have key
	bool useKey(std::string name);
	
	//door will call setNextWorld to initiate the next level process
	void setNextWorld(std::string name);
	//getNextWorld should return next world string and replace curWrld with nextWorld
	std::string getNextWorld();
private:

	//Map of keys -- using map to set false once used for GUI purposes(only showing unused keys for example)
	std::map<std::string, bool>keys;

	//string for current world -- used when saving 
	std::string curWorld;
	//string of next world
	std::string nextWorld;
	//flag for when door object sets next world
	bool changeWorld;
	

	//player's health
	int health;
	//flag for sprint
	bool running;
	//impulse when walking
	float speedWalking;
	//impulse when sprinting
	float speedRunning;
	//max velocity changes whether sprinting or not
	float speedMax;

	sf::Texture tex;
	sf::Sprite sprite;
	b2Body* phys;
	b2Body* createPhys(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_dynamicBody);
	GContactListener physListener;

};

#endif