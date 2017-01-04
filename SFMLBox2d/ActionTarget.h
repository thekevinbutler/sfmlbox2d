#ifndef ACTIONTARGET_H
#define ACTIONTARGET_H
#include <functional>
#include "SFML\Graphics.hpp"
#include "Action.h"
#include <list>
class ActionTarget
{
public:
	using FuncType = std::function<void(const sf::Event&)>;
	ActionTarget();

	bool processEvent(const sf::Event& event)const;
	void processEvents()const;

	void bind(const Action& action, const FuncType& callback);
	void unbind(const Action& action);
private:
	std::list<std::pair<Action, FuncType>> _eventsRealTime;
	std::list<std::pair<Action, FuncType>> _eventsPoll;
};

#endif