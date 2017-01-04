#include "ActionTarget.h"

ActionTarget::ActionTarget()
{}

bool ActionTarget::processEvent(const sf::Event& event)const
{
	bool res = false;
	for (auto& action : _eventsPoll)
	{
		if (action.first == event)
		{
			action.second(event);
			res = true;
			break;
		}
	}
	return res;
}

void ActionTarget::processEvents()const
{
	for (auto& action : _eventsRealTime)
	{
		if (action.first.test())
			action.second(action.first._event);
	}
}

void ActionTarget::bind(const Action& action, const FuncType& callback)
{
	if (action._type & Action::Type::RealTime)
		_eventsRealTime.emplace_back(action, callback);
	else
		_eventsPoll.emplace_back(action, callback);
}

void ActionTarget::unbind(const Action& action)
{
	auto remove_func = [&action](const std::pair<Action, FuncType>& pair) -> bool
	{
		return pair.first == action;
	};
	if (action._type & Action::Type::RealTime)
		_eventsRealTime.remove_if(remove_func);
	else
		_eventsPoll.remove_if(remove_func);
}

