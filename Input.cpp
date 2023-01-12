#include "Input.h"

namespace input {

ButtonState::ButtonState(milliseconds pressedAt, ControllerButton button)
	: button(button), pressedAt(pressedAt) {}

void ButtonState::Released(milliseconds releasedAt) {
	this->releasedAt = releasedAt;
	holdDuration = releasedAt - pressedAt;
}

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
		return handleInput(*forwardedEvent);
	}

	if (auto forwardedEvent = std::get_if<event::ControllerButtonRelease>(event)) {
		return handleInput(*forwardedEvent);
	}
}

void ActionSet::handleInput(event::ControllerButtonPress& event) {
	ButtonState buttonState{event.timestamp(), event.button};
	buttonStateArray[buttonState.button] = buttonState;

	switch (event.button) {
	case event::A:
		buttonA_->execute();
		break;
	case event::B:
		buttonB_->execute();
		break;
	}
}

void ActionSet::handleInput(event::ControllerButtonRelease& event) {
	optional<ButtonState> buttonState = buttonStateArray[event.button];

	if (buttonState.has_value()) {
		buttonState.value().Released(event.timestamp());

		BOOST_LOG_TRIVIAL(debug) << "Button " 
														 << buttonState.value().button 
			                       << " has been held for "
			                       << buttonState.value().holdDuration.value().count();

		buttonStateArray[event.button] = nullopt;
	} else {
		BOOST_LOG_TRIVIAL(warning) << "Expected a button press event, found none";
	}

	switch (event.button) {
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
