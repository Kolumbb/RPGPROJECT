#pragma once

#include "../ResourcePath.hpp"
#include "Menu.hpp"
#include "Gui.hpp"
#include "../StateData.hpp"


class PauseMenu : public Menu {
	private:
		//Variables & Resources
	protected:
		//Initializers
		auto initText() -> void;
		auto initBackground() -> void;
		auto initGui(u_short offsetB = 0) -> void;
		auto updateGui(const float& dt, const sf::Vector2f& mousePosition) -> bool;

	public:

		//Constructors & Destructors
		PauseMenu(
            StateData& stateData, const u_short& buttonsWidth, const u_short& characterSize, bool menu = false
        );
		virtual ~PauseMenu();



		//Modifiers
		//Update methods
		auto update(const float& dt, const sf::Vector2f& mousePosition) -> void;

		//Render methods
		auto render(std::shared_ptr<sf::RenderTarget> target) -> void;
		auto renderBackground(std::shared_ptr<sf::RenderTarget> target) -> void;
		auto renderGui(std::shared_ptr<sf::RenderTarget> target) -> void;



	};
