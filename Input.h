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
  void execute();
};
class MenuConfirmCommand : public Command {
  void execute();
};
class DebugCommand : public Command {
  void execute();
};

enum ActionSetId { GAME_ACTION_SET, MENU_ACTION_SET };

class ActionSet {
public:
  virtual ActionSetId id() = 0;

  void handleInput(event::Event* event);

protected:
  Command* buttonA_;
  Command* buttonB_;
};

class GameActionSet : public ActionSet {
public:
  GameActionSet();
  ActionSetId id();
};

class MenuActionSet : public ActionSet {
public:
  MenuActionSet();

  ActionSetId id();
};
} // namespace Input
