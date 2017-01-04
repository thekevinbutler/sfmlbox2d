#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "Player.h"
#include "World.h"
#include "Box2D\Box2D.h"
#include <list>
#include "Camera.h"
#include <string>
class Game
{
public:
	Game();
	int run(int minFPS);
private:
	void processEvents();
	void update(sf::Time dt);
	void draw();

	//gameWorld
	World gameWorld;
	//box2d stuff
	b2World world;

	sf::RenderWindow window;
	
	Camera cam;
	Player player;
	//text!!Debug
	sf::Font font;
	sf::Text debugText;
	sf::View viewGUI;
	void dMessage(std::string msg, sf::Vector2f pos);
};

#endif