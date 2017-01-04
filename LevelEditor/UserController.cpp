#include "UserController.h"
const float camStep = 0.05f;
#define _USE_MATH_DEFINES
#include <math.h>

UserController::UserController(sf::RenderWindow& pwindow, EditorView* eView, World& pworld, PhysProperties* physMenu) : cam(eView), window(pwindow), world(pworld)
{
	bind(Action(sf::Keyboard::W), [this](const sf::Event&)
	{
		cam->move(0.0f, -camStep);
	});
	bind(Action(sf::Keyboard::A), [this](const sf::Event&)
	{
		cam->move(-camStep, 0.0f);
	});
	bind(Action(sf::Keyboard::S), [this](const sf::Event&)
	{
		cam->move(0.0f,camStep);
	});
	bind(Action(sf::Keyboard::D), [this](const sf::Event&)
	{
		cam->move(camStep, 0.0f);
	});
	bind(Action(sf::Keyboard::Equal, Action::Type::Pressed), [this](const sf::Event&)
	{
		cam->zoomIn();
	});
	bind(Action(sf::Keyboard::Num1, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_PLAYGROUND_FRONT);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Num2, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_PLAYGROUND_MID);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Num3, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_PLAYGROUND_BACK);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Num4, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_BACKGROUND_FRONT);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Num5, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_BACKGROUND_BACK);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Num0, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.setActiveLayer(World::ELayer::EL_PHYS);
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Numpad1, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_PLAYGROUND_FRONT).toggleHide();
	});
	bind(Action(sf::Keyboard::Numpad2, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_PLAYGROUND_MID).toggleHide();
	});
	bind(Action(sf::Keyboard::Numpad3, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_PLAYGROUND_BACK).toggleHide();
	});
	bind(Action(sf::Keyboard::Numpad4, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_BACKGROUND_FRONT).toggleHide();
	});
	bind(Action(sf::Keyboard::Numpad5, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_BACKGROUND_BACK).toggleHide();
	});
	bind(Action(sf::Keyboard::Numpad0, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.getLayer(World::ELayer::EL_PHYS).toggleHide();
	});
	bind(Action(sf::Keyboard::Dash, Action::Type::Pressed), [this](const sf::Event&)
	{
		cam->zoomOut();
	});
	bind(Action(sf::Keyboard::P, Action::Type::Pressed), [this](const sf::Event&)
	{
		pBrush.start();
		eEdit = EDIT_PHYS;
	});
	bind(Action(sf::Keyboard::Delete, Action::Type::Pressed), [this](const sf::Event&)
	{
		if (activeObj)
		{
			world.getActiveLayer().removeObj(activeObj);
		}
		activeObj = NULL;
	});
	bind(Action(sf::Keyboard::Escape, Action::Type::Pressed), [this](const sf::Event&)
	{
		if (activeObj)
		{ 
			switch (eEdit)
			{
			case EDIT_NONE:
				activeObj = NULL;
				break;
			case EDIT_GRAB:
				activeObj->setPosition(originalPos);
				eEdit = EDIT_NONE;
				break;
			case EDIT_ROT:
				activeObj->setRotation(originalRot);
				eEdit = EDIT_NONE;
				break;
			case EDIT_SCALE:
				activeObj->setScale(originalScale);
				eEdit = EDIT_NONE;
				break;
			case EDIT_PHYS:
				pBrush.end();
			}
		}
	});
	bind(Action(sf::Keyboard::R, Action::Type::Pressed), [this](const sf::Event&)
	{
		if (activeObj)
		{
			if (eEdit = EDIT_ROT)
			{
				eEdit = EDIT_NONE;
			}
			eEdit = EDIT_ROT;
			editPos = getMouseCoords();
			originalRot = activeObj->getRotation();
		}
		
	});
	bind(Action(sf::Keyboard::T, Action::Type::Pressed), [this](const sf::Event&)
	{
		if (activeObj)
		{
			if (eEdit = EDIT_SCALE)
			{
				eEdit = EDIT_NONE;
			}
			eEdit = EDIT_SCALE;
			editPos = getMouseCoords();
			originalScale = activeObj->getScale();
		}

	});
	bind(Action(sf::Keyboard::F5, Action::Type::Pressed), [this](const sf::Event&)
	{
		world.save("world1.txt");
	});
	bind(Action(sf::Mouse::Left, Action::Type::Pressed), [this](const sf::Event&)
	{
		switch (eEdit)
		{
		case EDIT_NONE:
		{
			if (activeObj)
			{
				editPos = getMouseCoords();
				originalPos = activeObj->getPosition();
				eEdit = EDIT_GRAB;
			}

			VisibleObject* temp = world.getActiveLayer().getObjectUnderCursor(getMouseCoords());
			if (temp)
			{
				setActive(temp);
				updateProperties = true;
			}
		}break;
		case EDIT_PHYS:
		{
			if (!pBrush.addPoint(getMouseCoords()))
			{
				world.setActiveLayer(World::ELayer::EL_PHYS);
				world.getPhysLayer().addPhys(pBrush.buildPhysObj());
				pBrush.end();
				eEdit = EDIT_NONE;
			}
		}break;
		}

		
	});
	bind(Action(sf::Mouse::Left, Action::Type::Released), [this](const sf::Event&)
	{
		if (eEdit != EDIT_PHYS)
		{
			eEdit = EDIT_NONE;
		}
	});
	bind(Action(sf::Mouse::Right, Action::Type::Pressed), [this](const sf::Event&)
	{
		setActive(oBrush.addCurObject());
		if (activeObj != NULL)
		{
			activeObj->setPosition(getMouseCoords());
			world.getActiveLayer().addObj(activeObj);
		}
	});

	pBrush.init(physMenu);
	updateProperties = false;
	eEdit = EDIT_NONE;
}
void UserController::processEvents()
{
	ActionTarget::processEvents();
}
void UserController::update(sf::Time dt)
{
	switch (eEdit)
	{
	case EDIT_GRAB:
		calcGrab();
		break;
	case EDIT_ROT:
		calcRot();
		break;
	case EDIT_SCALE:
		calcScale();
		break;
	}
}
void UserController::draw()
{
	if (activeObj != NULL)
	{
		EditorView::EDrawView drawView = world.isLayerBG() ? EditorView::EDrawView::DRAWVIEW_BACKGROUND : EditorView::EDrawView::DRAWVIEW_FOREGROUND;
	
		cam->setView(drawView);
		sf::Vector2f size(activeObj->getGlobalBounds().width, activeObj->getGlobalBounds().height);
		sf::RectangleShape cursor(size);
		cursor.setOrigin(size.x / 2.0f, size.y / 2.0f);
		cursor.setPosition(activeObj->getPosition());
		cursor.setOutlineThickness(2.0f);
		cursor.setOutlineColor(sf::Color::Green);
		cursor.setFillColor(sf::Color::Transparent);
		window.draw(cursor);

	}
	window.draw(oBrush.draw(getMouseCoords()));
}

void UserController::setActive(VisibleObject* obj)
{
	activeObj = obj;
	updateProperties = true;
}

void UserController::calcGrab()
{
	sf::Vector2f posUpdate = getMouseCoords();
	
	sf::Vector2f objPos = activeObj->getPosition();
	objPos.x += (posUpdate.x - editPos.x);
	objPos.y += (posUpdate.y - editPos.y);
	activeObj->setPosition(objPos);

	editPos = posUpdate;
}
void UserController::calcRot()
{
	//pivot
	sf::Vector2f objPos = activeObj->getPosition();
	//rot arm
	sf::Vector2f posUpdate = getMouseCoords();
	//

	float angle = atan2(posUpdate.y - objPos.y, posUpdate.x - objPos.x);
	float degAngle = (angle * 180) / M_PI;
	activeObj->setRotation(degAngle);
}

void UserController::calcScale()
{
	sf::Vector2f objPos = activeObj->getPosition();
	float defaultDistance = sqrt(pow(editPos.x - objPos.x, 2) + pow(editPos.y - objPos.y, 2));
	float currentDistance = sqrt(pow(getMouseCoords().x - objPos.x, 2) + pow(getMouseCoords().y - objPos.y, 2));
	activeObj->setScale(originalScale * (currentDistance / defaultDistance));
}
sf::Vector2f UserController::getMouseCoords()
{
	EditorView::EDrawView drawView = world.isLayerBG() ? EditorView::EDrawView::DRAWVIEW_BACKGROUND : EditorView::EDrawView::DRAWVIEW_FOREGROUND;
	cam->setView(drawView);
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}