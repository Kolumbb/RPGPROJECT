#include "Menu.hpp"


//Menu Class



//Constructors & Destructors

Menu::Menu(StateData& state_data, u_short buttonsWidth, u_short characterSize) : stateData(state_data), buttonsWidth(buttonsWidth), characterSize(characterSize) {};


//Other Public methods
auto Menu::isButtonPressed(const std::string &name) -> bool {
    if(this->buttons[name]->isPressed()) return true;
    else return false;
}