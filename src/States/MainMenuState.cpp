#include "MainMenuState.hpp"




//Initializers

auto MainMenuState::initBackground(const std::filesystem::path& path) -> void {

	if (!this->texture.loadFromFile(path.string()))
		this->shape.setFillColor(sf::Color::Red);
	
	this->shape.setTexture(&this->texture);
	this->shape.setSize(
		sf::Vector2f(
			this->stateData.gfxSettings->resolution.width, 
			this->stateData.gfxSettings->resolution.height
		)
	);
}

auto MainMenuState::initKeyBinds(const std::filesystem::path& path)-> void {

	auto file = std::fstream(path);

	if (file) {
		auto key = std::string();
		auto key_value = std::string();
		
		while (file >> key >> key_value) {
			this->keyBinds[key] = this->stateData.supportedKeys[key_value];
		}
	}
	file.close();

	/*for (auto& it : this->keyBinds) {
		std::cout << it.first << " " << it.second << "\n";

	}*/

}

auto MainMenuState::initButtons(const sf::Font& font, u_short offsetB) -> void {
    
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
			sf::Color(20, 20, 20, 0), font
		);
	}
	
}
auto MainMenuState::initButtonNames() -> void{
    this->buttonNames = std::vector<std::string>{"New Game", "Settings", "Editor", "Quit"};
}
//Accessors & Modifiers

//Constructors & Destructors
MainMenuState::MainMenuState(StateData& stateData) : State(stateData) {
        this->initKeyBinds();
        this->initBackground();
        this->initButtonNames();
        this->initButtons(this->stateData.font);
    }



//Update methods
auto MainMenuState::update(const float& dt) -> void {
	this->timer.updateKeyTime(dt);
    this->updateMousePos(this->stateData.window->getDefaultView());
    this->resolutionChanged();

	this->updateButtons(dt);
	
}

auto MainMenuState::updateButtons(const float& dt) -> void {
	for (auto& it : this->buttons) it.second->update(dt, this->mousePosWindow);


	if (this->buttons["New Game"]->isPressed() && this->timer.getKeyTime())
		this->stateData.states.push(std::make_shared<GameState>(this->stateData));

	if (this->buttons["Settings"]->isPressed() && this->timer.getKeyTime())
		this->stateData.states.push(std::make_shared<SettingsState>(this->stateData));

	if (this->buttons["Editor"]->isPressed() && this->timer.getKeyTime())
		this->stateData.states.push(std::make_shared<EditorState>(this->stateData));

	if (this->buttons["Quit"]->isPressed() && this->timer.getKeyTime())
		this->stateData.states.pop();
}



//Render methods

auto MainMenuState::render(sf::RenderTarget* target) -> void {
	target->draw(this->shape);
	this->renderButtons(target);
}


auto MainMenuState::renderButtons(sf::RenderTarget* target) -> void {
	for (auto& it : this->buttons) it.second->render(target);
}

auto MainMenuState::resolutionChanged() -> void{
    if(this->stateData.gfxSettings->resolution.width != static_cast<int>(this->shape.getSize().x)){
        this->shape.setSize(
            sf::Vector2f(
                this->stateData.gfxSettings->resolution.width,
                this->stateData.gfxSettings->resolution.height
            )
        );
        this->initButtons(this->stateData.font);
    }
}
