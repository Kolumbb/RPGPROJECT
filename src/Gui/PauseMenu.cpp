#include "PauseMenu.hpp"


//Initializers


auto PauseMenu::initGui(u_short offsetB) -> void {
	this->buttonNames = std::vector<std::string>{
        "Resume",
        "Save",
        "Load",
        "Quit"
    };

	auto tmp = sf::Text();
	tmp.setCharacterSize(this->characterSize);

	for (int i = 0; i < buttonNames.size(); i++) {
		
		tmp.setString(buttonNames[i]);
		this->buttons[tmp.getString()] = std::make_unique<gui::Button>(
			this->stateData.gfxSettings->resolution.width / 2.f - (this->buttonsWidth / 2.f) - tmp.getGlobalBounds().width / 2.f, //pos_x
			400.f + (60 * i), //pos_y
			buttonsWidth, //width
			50.f, //height
			buttonNames[i], this->characterSize,
			sf::Color(0, 0, 0, 255),
			sf::Color(250, 250, 250, 250),
			sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0),
			sf::Color(150, 150, 150, 0),
			sf::Color(20, 20, 20, 0), this->stateData.font
		);
	}
}

auto PauseMenu::initText() -> void {
	this->text.setFont(this->stateData.font);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("PAUSED");
	this->text.setPosition(
		sf::Vector2f(
			this->stateData.gfxSettings->resolution.width / 2 - this->text.getGlobalBounds().width / 2.f,
			100
		)
	);
}

auto PauseMenu::initBackground() -> void {
	this->background.setSize(
        sf::Vector2f(
            this->stateData.gfxSettings->resolution.width / 2.f,
            this->stateData.gfxSettings->resolution.height
            )
    );
	this->background.setPosition(sf::Vector2f(this->stateData.gfxSettings->resolution.width / 4.f, 0));
	this->background.setFillColor(sf::Color(0, 0, 0, 100));

	this->transparentBackground.setSize(
        sf::Vector2f(
                this->stateData.gfxSettings->resolution.width,
                this->stateData.gfxSettings->resolution.height
        )
    );
	this->transparentBackground.setPosition(0, 0);
	this->transparentBackground.setFillColor(sf::Color(215, 215, 215, 100));

}

//Constructors & Destructors

//
PauseMenu::PauseMenu(StateData& stateData, const u_short& buttonsWidth, const u_short& characterSize, bool menu) : Menu(stateData, buttonsWidth, characterSize) {
	this->initGui();
	this->initText();
	this->initBackground();
}

PauseMenu::~PauseMenu() {
  std::cout <<"PauseMenu deleted\n";
}


//Update methods
auto PauseMenu::update(const float& dt, const sf::Vector2f& mousePosition) -> void {
    for (auto& it : this->buttons) it.second->update(dt, mousePosition);
    
}

//Render methods
auto PauseMenu::render(std::shared_ptr<sf::RenderTarget> target) -> void {
	this->renderBackground(target);
	this->renderGui(target);
}

auto PauseMenu::renderBackground(std::shared_ptr<sf::RenderTarget> target)  -> void {
	target->draw(this->transparentBackground);
	target->draw(this->background);
	target->draw(this->text);
}

auto PauseMenu::renderGui(std::shared_ptr<sf::RenderTarget> target) -> void {
	for(auto & it : this->buttons) it.second->render(target);
}

//Other public methods

