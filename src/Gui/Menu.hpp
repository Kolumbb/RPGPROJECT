#pragma once

#include "../ResourcePath.hpp"
#include "../StateData.hpp"
#include "Gui.hpp"

class Menu {
protected:
    u_short buttonsWidth;
    u_short characterSize;
    StateData& stateData;
    std::vector<std::string> buttonNames;
    sf::Text text;
    sf::RectangleShape transparentBackground;
    sf::RectangleShape background;
    std::map<std::string, std::unique_ptr<gui::Button>> buttons;

    //Initializers
    virtual auto initText() -> void = 0;
    virtual auto initGui(u_short offsetB = 0) -> void = 0;
    virtual auto initBackground() -> void = 0;

    
    
    //Update methods
    //Render methods
	virtual auto render(sf::RenderTarget* target) -> void = 0;
	virtual auto renderBackground(sf::RenderTarget* target) -> void = 0;
	virtual auto renderGui(sf::RenderTarget* target) -> void = 0;




public:

    //Constructors & Destructors
	Menu(StateData& state_data, u_short buttonsWidth, u_short characterSize);
	virtual ~Menu() = default;

    //Other methods
    auto isButtonPressed(const std::string& name) -> bool;
};
