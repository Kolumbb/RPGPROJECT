#pragma once

#include "../ResourcePath.hpp"
#include "Menu.hpp"
#include "../StateData.hpp"
#include "Gui.hpp"


class DisplaySettingsMenu : public Menu {
private:
	//Resources && Variables
	std::map<std::string, std::unique_ptr<gui::DropDownList>> dropDownLists;

protected:
	//Initializers
	auto initText() -> void;
	auto initBackground() -> void;
    auto initGui(u_short offsetB = 3) -> void;
    auto initDropDownLists() -> void;
    auto updateGui(const float& dt, const sf::Vector2f& mousePosition) -> void;

public:
	//Constructors & Destructors
	DisplaySettingsMenu(StateData& stateData, const u_short& buttons, const u_short& character_size, bool menu = false);
	~DisplaySettingsMenu() = default;

	//Public methods
    
	//Update methods
	auto update(const float& dt, const sf::Vector2f& mousePosition) -> void;

	//Render methods
	auto render(sf::RenderTarget* target) -> void;
	auto renderBackground(sf::RenderTarget* target) -> void;
	auto renderGui(sf::RenderTarget* target) -> void;
    
    //Modifiers
    auto setResolution() -> void;
    auto setFullScreen() -> void;
    //Getters
    
};
