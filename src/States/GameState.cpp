#include "GameState.hpp"


//Initializers
auto GameState::initKeyBinds(const std::filesystem::path& path) -> void {

  auto file = std::fstream(path);

  if (file) {
    auto key = std::string();
    auto key_value = std::string();

    while (file >> key >> key_value) {
      this->keyBinds[key] = this->stateData.supportedKeys[key_value];
      std::cout << keyBinds[key] << " " << this->stateData.supportedKeys[key_value] << "\n";
    }
  }
  file.close();
}

auto GameState::initEntities() -> void {
    this->entities.push_back(std::make_shared<Player>(sf::Vector2f(200, 400), 100));
    this->entities.push_back(std::make_shared<Slime>(sf::Vector2f(400, 600), 40));
}

auto GameState::initPausedMenu() -> void {
  this->pMenu = std::make_unique<PauseMenu>(this->stateData, 150, 16);
}

auto GameState::initTileMap() -> void {
  this->map = std::make_unique<TileMap>(this->stateData.gridSizeF, 150, 50);
  this->map->loadMapFromFile();
}

auto GameState::initView() -> void {
  this->gameView.setSize(
      sf::Vector2f(this->stateData.gfxSettings->resolution.width,
                   this->stateData.gfxSettings->resolution.height
                   )
      );
  this->gameView.setCenter(
      sf::Vector2f(this->stateData.gfxSettings->resolution.width / 2.f,
                   this->stateData.gfxSettings->resolution.height / 2.f
                   )
      );
}

auto GameState::initBufferedRender() -> void {
  this->renderTexture.create(
        this->stateData.gfxSettings->resolution.width,
        this->stateData.gfxSettings->resolution.height
        );
  this->renderSprite.setTexture(this->renderTexture.getTexture());
  this->renderSprite.setTextureRect(
      sf::IntRect (
          0,
          0,
          this->stateData.gfxSettings->resolution.width,
          this->stateData.gfxSettings->resolution.height
          )
      );
}

auto GameState::initPlayerGui() -> void {
    this->playerGui = std::make_unique<PlayerGui>(this->entities[0]->getHealth());
}


GameState::GameState(StateData& state_data) : State(state_data), paused(false) {
  this->initKeyBinds();
  this->initPausedMenu();
  this->initEntities();
  this->initTileMap();
  this->initView();
  this->initBufferedRender();
  this->initPlayerGui();
}



auto GameState::update(const float& dt) -> void {
  this->timer.updateKeyTime(dt);
  this->updateMousePos(this->gameView);
  this->updateKeyBindsInput(dt);

  // Update unpaused
  if (!this->paused) {
    this->updateUnPaused(dt);
  }
  // Update paused
  else {
    this->updatePaused(dt);
  }
}

//Update Unpaused
auto GameState::updateUnPaused(const float& dt) -> void {
  this->updateView();
  this->playerGui->update(dt, this->entities[0]->getHealth());
  this->updateTileMap(dt);
  for(auto it : this->entities)
      it->update(dt);
  this->updateUserInput();
}

//Update Paused
auto GameState::updatePaused(const float& dt) -> void {
  this->pMenu->update(dt, this->mousePosWindow);
  this->updateButtons(dt);
}

auto GameState::updateUserInput() -> void {
    if (!this->entities[0]->getAttack()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_RIGHT"])))
        this->entities[0]->move(1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_LEFT"])))
        this->entities[0]->move(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_UP"])))
        this->entities[0]->move(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_DOWN"]))) {
        this->entities[0]->move(0, 1);
        }
    }

}

auto GameState::updateKeyBindsInput(const float& dt) -> void {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CLOSE"])) &&this->timer.getKeyTime())
    if (!this->paused)
        this->paused = true;
    else
        this->paused = false;
}

auto GameState::updateView() -> void {
    this->gameView.setCenter(this->entities[0]->getPositionF());
}

auto GameState::updateTileMap(const float& dt) -> void {
    this->map->update(dt, this->entities);

}

//Render methods
auto GameState::render(sf::RenderTarget* target) -> void {
this->renderTexture.clear();
  this->renderUnPaused(&this->renderTexture);
  if (this->paused)
    this->renderPaused(&this->renderTexture);

  this->renderTexture.display();
  this->renderSprite.setTexture(this->renderTexture.getTexture());
  target->draw(this->renderSprite);
}

auto GameState::renderPaused(sf::RenderTarget* target) -> void {
  this->renderTexture.setView(this->renderTexture.getDefaultView());
  this->pMenu->render(target);
}

auto GameState::renderUnPaused(sf::RenderTarget* target) -> void {
  this->renderTexture.setView(this->gameView);
  this->playerGui->render(target);
  this->map->render(&this->renderTexture);

  for(auto& it :this->entities)
      it->render(&this->renderTexture);
}

auto GameState::updateButtons(const float &dt) -> void {
  if (this->pMenu->isButtonPressed("Quit"))
    this->stateData.states.pop();
  else if (this->pMenu->isButtonPressed("Resume"))
    this->paused = !this->paused;
}

auto GameState::updatePlayerHealth() -> void{
    this->entities[0]->getHealth();
}



