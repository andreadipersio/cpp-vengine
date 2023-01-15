#pragma once

#include <array>
#include <boost/log/trivial.hpp>
#include <chrono>
#include <fmt/core.h>
#include <optional>
#include <variant>

#include "Event.h"

using event::ControllerButton;
using std::chrono::milliseconds;
using std::optional, std::nullopt;

namespace input {

class ButtonState {
public:
	ControllerButton button;
	milliseconds pressedAt;
	optional<milliseconds> releasedAt;
	optional<milliseconds> holdDuration;
	
	ButtonState(milliseconds, ControllerButton);
	void Released(milliseconds);
};

class Command {
public:
	virtual void execute() = 0;
};

class AttackCommand : public Command {
public:
	void execute();
};
class MenuConfirmCommand : public Command {
	void execute();
};
class DebugCommand : public Command {
	void execute();
};

enum ActionSetId {
	GAME_ACTION_SET, MENU_ACTION_SET
};

class ActionSet {
public:
	std::array<optional<ButtonState>, 20> buttonStateArray;

	virtual ActionSetId id() const = 0;

	Command* handleInput(event::ControllerButtonPress&);
	Command* handleInput(event::ControllerButtonRelease& event);
	Command* handleInput(event::Event*);

protected:
	Command* buttonA_;
	Command* buttonB_;
};

class GameActionSet : public ActionSet {
public:
	GameActionSet();
	ActionSetId id() const;
};

class MenuActionSet : public ActionSet {
public:
	MenuActionSet();
	ActionSetId id() const;
};
} // namespace input
