#include "State.hpp"

//Protected update methods
auto State::updateMousePos(const sf::View& view) -> void {

  this->mousePosWindow = this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window));
  this->mousePosU = sf::Vector2u(
      this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window)).x /
          this->stateData.gridSizeF,
      this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window)).y/
          this->stateData.gridSizeF
  );



  this->stateData.window->setView(view);
    this->mousePosGrid = sf::Vector2u(
      this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window)).x /
          this->stateData.gridSizeF,
      this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window)).y/
          this->stateData.gridSizeF
    );
    this->stateData.window->setView(this->stateData.window->getDefaultView());

}

//Constructors & Destructors
State::State(StateData& stateData): stateData(stateData), mousePosU(sf::Vector2u()),
    mousePosGrid(sf::Vector2u(static_cast<u_short>(mousePosU.x), static_cast<u_short>(mousePosU.y))){}














