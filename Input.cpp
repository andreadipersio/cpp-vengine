#include "Input.h"

namespace input {

void AttackCommand::execute() {
	BOOST_LOG_TRIVIAL(debug) << "Attack!!!";
}

void MenuConfirmCommand::execute() {
	BOOST_LOG_TRIVIAL(debug) << "Menu selection confirmed";
}

void DebugCommand::execute() {
	BOOST_LOG_TRIVIAL(debug) << "Debug time!";
}

void ActionSet::handleInput(event::Event* event) {
	if (auto forwardedEvent = std::get_if<event::ControllerButtonPress>(event)) {
		return handleInput(forwardedEvent);
	}

	if (auto forwardedEvent = std::get_if<event::ControllerButtonRelease>(event)) {
		return handleInput(forwardedEvent);
	}
}

void ActionSet::handleInput(event::ControllerButtonPress* event) {
	switch (event->button) {
	case event::A:
		buttonA_->execute();
		break;
	case event::B:
		buttonB_->execute();
		break;
	}
}

void ActionSet::handleInput(event::ControllerButtonRelease* event) {
	switch (event->button) {
	case event::A:
		buttonA_->execute();
		break;
	case event::B:
		buttonB_->execute();
		break;
	}
}

GameActionSet::GameActionSet() {
	buttonA_ = new AttackCommand;
	buttonB_ = new DebugCommand;
}

ActionSetId GameActionSet::id() const {
	return GAME_ACTION_SET;
}

MenuActionSet::MenuActionSet() {
	buttonA_ = new MenuConfirmCommand;
	buttonB_ = new DebugCommand;
}

ActionSetId MenuActionSet::id() const {
	return MENU_ACTION_SET;
}
} // namespace Input
