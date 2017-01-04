#ifndef CAMERA_H
#define CAMERA_H
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "LayeredView.h"
class Camera : public LayeredView
{
public:
	Camera() = delete;
	Camera(sf::RenderWindow& pWindow, Player& player);
	void init();
	void setTarget(Player& player);
	void updatePos(sf::Time dt);
private:
	float elapsedTime;
	bool isGroundCam;
	sf::Vector2f initialZoom;
	sf::Vector2f zoomRes;
	sf::Vector2f lerpPos;
	Player& target;
};
#endif