#include "EditorView.h"
#include "SFML\OpenGL.hpp"
EditorView::EditorView(sf::RenderWindow& pwindow) : window(pwindow), zoomStep(0.1f)
{
	mapCenter = sf::Vector2f(0.0f, 0.0f);
	bgScaleFrac = 2.0f;
	bgCenterFrac = 0.75;
}
void EditorView::init()
{
	zoomFactor = 1.0f;
	initialZoom = window.getView().getSize();
	zoomRes = initialZoom;
	setSize(initialZoom);
	setCenter(sf::Vector2f(0.0f, 0.0f));
}
void EditorView::zoomIn()
{
	if (zoomFactor > 0.1)
	{
		zoomFactor -= zoomStep;
		setZoom();
	}
}

void EditorView::zoomOut()
{
	zoomFactor += zoomStep;
	setZoom();
}

void EditorView::zoomReset()
{
	zoomFactor = 1.0f;
	setZoom();
}

void EditorView::setCenter(sf::Vector2f newCenter)
{
	globalPos = newCenter;
	playGround.setCenter(globalPos);
	sf::Vector2f bgOffset;
	bgOffset.x = globalPos.x - (mapCenter.x * bgCenterFrac);
	bgOffset.y = globalPos.y - (mapCenter.y * bgCenterFrac);
	backGround.setCenter(bgOffset);
}

void EditorView::setZoom()
{
	zoomRes.x = initialZoom.x * zoomFactor;
	zoomRes.y = initialZoom.y * zoomFactor;
	setSize(zoomRes);
}
void EditorView::setSize(sf::Vector2f newSize)
{
	playGround.setSize(newSize);
	sf::Vector2f bgSize = newSize;
	bgSize.x *= bgScaleFrac;
	bgSize.y *= bgScaleFrac;
	backGround.setSize(bgSize);
}

void EditorView::setView(EDrawView view)
{
	switch (view)
	{
	case DRAWVIEW_BACKGROUND:
		window.setView(backGround);
		break;
	case DRAWVIEW_FOREGROUND:
		window.setView(playGround);
		break;
	}
	
}
void EditorView::move(float x, float y)
{
	sf::Vector2f newPos = globalPos;
	newPos.x += x;
	newPos.y += y;
	setCenter(newPos);
}