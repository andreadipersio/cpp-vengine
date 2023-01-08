#pragma once

#include <boost/log/trivial.hpp>
#include <variant>

#include "Event.h"

namespace input {

class Command {
public:
  virtual void execute() = 0;
};

class AttackCommand : public Command {
public:
  void execute() { BOOST_LOG_TRIVIAL(debug) << "Attack!!!"; }
};
class MenuConfirmCommand : public Command {
  void execute() { BOOST_LOG_TRIVIAL(debug) << "Menu selection confirmed"; }
};
class DebugCommand : public Command {
  void execute() { BOOST_LOG_TRIVIAL(debug) << "Debug time!"; }
};

enum ActionSetId { GAME_ACTION_SET, MENU_ACTION_SET };

class ActionSet {
public:
  virtual ActionSetId id() = 0;

  void handleInput(event::Event* event) {
    auto inputEvent = std::get_if<event::ControllerButtonPress>(event);

    if (!inputEvent) {
      return;
    }
    
    switch (inputEvent->button) {
    case event::A:
      buttonA_->execute();
      break;
    case event::B:
      buttonB_->execute();
      break;
    }
  }

protected:
  Command* buttonA_;
  Command* buttonB_;
};

class GameActionSet : public ActionSet {
public:
  GameActionSet() {
    buttonA_ = new AttackCommand;
    buttonB_ = new DebugCommand;
  }

  ActionSetId id() { return GAME_ACTION_SET; }
};

class MenuActionSet : public ActionSet {
public:
  MenuActionSet() {
    buttonA_ = new MenuConfirmCommand;
    buttonB_ = new DebugCommand;
  }

  ActionSetId id() { return MENU_ACTION_SET; }
};
} // namespace Input
