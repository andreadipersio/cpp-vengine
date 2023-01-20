
    find_package(Microsoft.GSL CONFIG REQUIRED)
    target_link_libraries(main PRIVATE Microsoft.GSL::GSL):

Menu Items: [New Game, Load Game, Settings]
                ^

Action Set: MenuActionSet

When: MenuActionSet.dpadDown->execute() -> Next Menu Item


Menu Items: [New Game, Load Game, Settings]
                          ^
When: MenuActionSet.buttonA_->execute() -> Enter Menu Item


