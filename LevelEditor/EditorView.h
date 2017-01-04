#ifndef EDITORVIEW_H
#define EDITORVIEW_H
#include "SFML\Graphics.hpp"
class EditorView
{
public:
	enum EDrawView
	{
		DRAWVIEW_BACKGROUND,
		DRAWVIEW_FOREGROUND

	};

	EditorView() = delete;
	EditorView(sf::RenderWindow& pwindow);
	//since window is not created during construction, view has garbage info
	void init();
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void move(float x, float y);
	void setSize(sf::Vector2f newSize);
	void setView(EDrawView view);
	void setCenter(sf::Vector2f newCenter);
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