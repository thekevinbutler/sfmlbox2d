#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include "ActionTarget.h"
#include "SFML\Graphics.hpp"
#include "VisibleObject.h"
#include "EditorView.h"
#include "World.h"
#include "ObjectBrush.h"
#include "PhysBrush.h"
#include "PhysProperties.h"

class UserController : public ActionTarget
{
public:
	bool updateProperties;
	enum EditType
	{
		EDIT_NONE,
		EDIT_GRAB,
		EDIT_SCALE,
		EDIT_ROT,
		EDIT_PHYS
	};

	UserController(sf::RenderWindow& pwindow, EditorView* eView, World& pworld, PhysProperties* physMenu);

	void update(sf::Time dt);
	void processEvents();
	void draw();

	void setActive(VisibleObject* obj);
	VisibleObject* getActive(){ return activeObj; }
	ObjectBrush& getBrush(){ return oBrush; }
	sf::Vector2f getMouseCoords();

private:
	EditType eEdit;
	sf::Vector2f editPos;
	sf::Vector2f originalPos;
	void calcGrab();
	
	void calcRot();
	float originalRot;

	void calcScale();
	sf::Vector2f originalScale;

	World& world;
	sf::RenderWindow& window;
	ObjectBrush oBrush;
	PhysBrush pBrush;

	VisibleObject* activeObj;
	EditorView* cam;
};
#endif