#ifndef LAYEREDVIEW_H
#define LAYEREDVIEW_H
#include "SFML\Graphics.hpp"
class LayeredView
{
public:
	enum EDrawView
	{
		DRAWVIEW_BACKGROUND,
		DRAWVIEW_FOREGROUND

	};

	LayeredView() = delete;
	LayeredView(sf::RenderWindow& pwindow);
	//since window is not created during construction, view has garbage info
	void init();
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void move(float x, float y);
	void setSize(sf::Vector2f newSize);
	void setZoomRes(float x, float y);
	void setView(EDrawView view);
	void setCenter(sf::Vector2f newCenter);
	sf::Vector2f getCenter(){ return globalPos; }
	sf::RenderWindow& getWindow(){ return window; }
	sf::Vector2f getSize(){ return playGround.getSize(); }
	sf::Vector2f getInitZoom(){ return initialZoom; }
private:
	sf::Vector2f mapCenter;
	sf::Vector2f globalPos;
	sf::View playGround;
	sf::View backGround;
	float bgScaleFrac;
	float bgCenterFrac;

	sf::RenderWindow& window;
	sf::Vector2f initialZoom;
	sf::Vector2f zoomRes;
	float zoomFactor;
	const float zoomStep;
	void setZoom();
};
#endif