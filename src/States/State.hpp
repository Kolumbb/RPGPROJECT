#pragma once
#include "../ResourcePath.hpp"
#include "../Gui/Gui.hpp"
#include "../StateData.hpp"

/*
	The idea is that the game has different states where player can do 
	different things and where resources would be placed. Every time when you
	enter new state you will play only with those solutions that have 
	been designed for a given state. That prevents from loading all resources
	at the same time when the game starts.
*/

class State {
private:
	//Private Variables & Resources
	
protected:

    //Protected Variables & Resources
    std::map<std::string, int> keyBinds;
    StateData& stateData;
    sf::Texture texture;
    my::Timer timer;
    std::vector<std::string>buttonNames;
    //For general purposes
    sf::Vector2f mousePosWindow;
    sf::Vector2u mousePosU;
protected:

    //For Game view purposes
    //Protected Initializers
    sf::Vector2u mousePosGrid;
    //Protected update methods
    auto updateMousePos(const sf::View& view) -> void;
public:

    //Constructors & Destructors
    State(StateData& stateData);
    virtual ~State() = default;

    //Public Update methods
    virtual auto update(const float& dt) -> void = 0;


    //Public Render methods
    virtual auto render(sf::RenderTarget* target) -> void = 0;

};
