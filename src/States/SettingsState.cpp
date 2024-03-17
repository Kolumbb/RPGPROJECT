#include "SettingsState.hpp"




//Initializers
auto SettingsState::initBackground(const std::filesystem::path& path) -> void {

	this->background = std::make_unique<sf::RectangleShape>();
	if (!this->texture.loadFromFile(path.string())) {
		this->background->setFillColor(sf::Color::Red);
	}
	this->background->setTexture(&this->texture);
	this->background->setSize(
		sf::Vector2f(
			this->stateData.gfxSettings->resolution.width, 
			this->stateData.gfxSettings->resolution.height
		)
	);
}

auto SettingsState::initKeyBinds(const std::filesystem::path& path) -> void {

	auto file = std::fstream(path);
	
	if (file) {
		auto key = std::string();
		auto key_value = std::string();
		while (file >> key >> key_value) {
			this->keyBinds[key] = this->stateData.supportedKeys[key_value];
		}
	}
	file.close();
}

auto SettingsState::initButtons(u_short offsetB) -> void {
    if(this->stateData.gfxSettings->resolution.width == 640) offsetB = 10;
    else if(this->stateData.gfxSettings->resolution.width == 1280) offsetB = 6;
    else if(this->stateData.gfxSettings->resolution.width == 1920) offsetB = 6;
    
    auto width =this->stateData.gfxSettings->resolution.width;
    
    for (int i = 0; i < this->buttonNames.size(); i++) {
        this->buttons[this->buttonNames[i]] = std::make_unique<gui::Button>(
            width/ 22.8f, //pos_x
            (width / 21.3f) * (i + offsetB), //pos_y
            width/ 8.53f, //width
            width / 25.6f, //height
            this->buttonNames[i], width / 80.f,
            sf::Color(0, 0, 0, 255),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(20, 20, 20, 0), this->stateData.font
            );
        }
}

auto SettingsState::initDisplaySettingsMenu() -> void{
	this->dMenu = std::make_unique<DisplaySettingsMenu>(this->stateData, 150, 16);
}

auto SettingsState::initButtonNames() -> void{
    this->buttonNames = std::vector<std::string>{"Display Settings","Controls", "Help", "Exit to Main Menu"};
}

//Constructors & Destructors
SettingsState::SettingsState(StateData& stateData) :
        State(stateData), paused(false) {
    this->initDisplaySettingsMenu();
    this->initKeyBinds();
    this->initBackground();
    this->initButtonNames();
    this->initButtons();

}

//Update Methods
auto SettingsState::update(const float& dt) -> void {
	this->timer.updateKeyTime(dt);
    this->updateMousePos(this->stateData.window->getDefaultView());


    if(!this->paused){
        this->updateSettingsState(dt);
    }
        //Update paused
    else {
        this->updateDisplaySettings(dt);
    }


}
auto SettingsState::updateSettingsState(const float& dt) -> void {
    this->updateButtons(dt);

}

auto SettingsState::updateDisplaySettings(const float& dt) -> void {
    this->dMenu->update(dt, this->mousePosWindow);
    if(this->dMenu->isButtonPressed("Confirm") && this->timer.getKeyTime()){
        this->dMenu->setResolution();
        this->initBackground();
        this->initButtons();
    }
    else if(this->dMenu->isButtonPressed("Back") && this->timer.getKeyTime()){
        this->paused = !this->paused;
    }

}



auto SettingsState::updateButtons(const float& dt) -> void {
	for (auto& it : this->buttons) it.second->update(dt, sf::Vector2f (this->mousePosWindow));

	if (this->buttons.at("Display Settings")->isPressed() && this->timer.getKeyTime()) paused = true;
	else if (this->buttons.at("Exit to Main Menu")->isPressed() && this->timer.getKeyTime()) {
		this->stateData.states.pop();
		
	}
	
}








//Render methods
auto SettingsState::render(sf::RenderTarget* target) -> void {
	this->renderUnPaused(target);

	if (this->paused)
		this->renderPaused(target);
}

auto SettingsState::renderPaused(sf::RenderTarget* target) -> void {
	this->dMenu->render(target);
}

auto SettingsState::renderUnPaused(sf::RenderTarget* target) -> void {
	target->draw(*this->background);
	this->renderButtons(target);
}

auto SettingsState::renderButtons(sf::RenderTarget* target) -> void {
    for (auto& it : this->buttons) it.second->render(target);
}




