#pragma once

#include "ResourcePath.hpp"
#include "StateData.hpp"
#include "States/GameState.hpp"
#include "States/MainMenuState.hpp"

class Game{
private:
    //Variables & Resources
    bool quit;
    sf::Clock clock;
    sf::Event event;
    float dt;
    StateData stateData;

    //Initializers
    auto initStates() -> void;
	
    //Update methods
    auto update(const float& dt) -> void;
    auto updateEvents() -> void;
    auto updateDt() -> void;
    //Render method
    auto render(sf::RenderTarget* target = nullptr) -> void;

    //Other private methods
    auto getQuit() -> const bool;

protected:
public:
    //Constructors & Destructors
    Game();
    ~Game() = default;

    //Public methods
    auto run() ->void;
};

