#include "Game.hpp"

//Initializers
auto Game::initStates() -> void {
    this->stateData.states.push(std::make_shared<MainMenuState>(this->stateData));
}

//Update methods
auto Game::update(const float& dt) -> void{
	this->updateEvents();
	if (!this->stateData.states.empty()) {
		this->stateData.states.top()->update(dt);
		
	}else this->quit = false;


}

auto Game::updateEvents() -> void {
	while (this->stateData.window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) this->stateData.window->close();
	}
	
}

auto Game::updateDt() -> void{
	this->dt = this->clock.getElapsedTime().asSeconds();
	this->clock.restart();
}

//Render methods
auto Game::render(sf::RenderTarget* target) -> void{
	target = this->stateData.window.get();
	if (target) {
		this->stateData.window->clear();

		if (!this->stateData.states.empty())
			this->stateData.states.top()->render(target);

		this->stateData.window->display();
	}
}

//Other private methods
auto Game::getQuit() -> const bool
{
    return this->quit;
}

//Constructors & Destructors
Game::Game() {
    this->initStates();
    this->dt = float();
    this->quit = true;
}

//Other public methods
auto Game::run() -> void{
	while (this->stateData.window->isOpen() && this->getQuit()) {
		this->updateDt();
		this->update(this->dt);
		this->render(this->stateData.window.get());
	}
}
