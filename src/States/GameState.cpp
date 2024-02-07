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

auto GameState::initPlayer() {
  this->player = std::make_shared<Player>();
}

auto GameState::initSlime() {
  this->slime = std::make_shared<Slime>();
}

auto GameState::initPausedMenu() -> void {
  this->pMenu = std::make_unique<PauseMenu>(this->stateData, 150, 16);
}

auto GameState::initTileMap() -> void {
  this->map = std::make_shared<TileMap>(this->stateData.gridSizeF, 150, 50);
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



GameState::GameState(StateData& state_data) : State(state_data), paused(false) {
  this->initKeyBinds();
  this->initPausedMenu();
  this->initPlayer();
  this->initSlime();
  this->initTileMap();
  this->initView();
  this->initBufferedRender();
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
  this->updateTileMap(dt);
  this->player->update(dt);
  this->slime->update(dt);
  this->updateUserInput(dt);
}

//Update Paused
auto GameState::updatePaused(const float& dt) -> void {
  this->pMenu->update(dt, this->mousePosWindow);
  this->updateButtons(dt);
}

auto GameState::updateUserInput(const float& dt) -> void {
  if (!this->player->getAttack()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_RIGHT"])))
      this->player->move(1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_LEFT"])))
      this->player->move(-1, 0);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->timer.getKeyTime())
    this->player->setAttack();

  if (!this->player->getJump()){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["MOVE_UP"])) &&this->timer.getKeyTime())
      this->player->setJump();

    if(!this->player->getJump()) this->player->fall();
    this->slime->fall();
  }





}

auto GameState::updateKeyBindsInput(const float& dt) -> void {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CLOSE"])) &&
      this->timer.getKeyTime())
    if (!this->paused)
      this->paused = true;
    else
      this->paused = false;
}

auto GameState::updateView() -> void {
  this->gameView.setCenter(this->player->getPositionF());
}

auto GameState::updateTileMap(const float& dt) -> void {
  this->map->update(dt, this->player, this->slime);

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
  this->map->render(&this->renderTexture, this->player);
  this->player->render(&this->renderTexture);
  this->slime->render(&this->renderTexture);
}

auto GameState::updateButtons(const float &dt) -> void {
  if (this->pMenu->isButtonPressed("Quit"))
    this->stateData.states.pop();
  else if (this->pMenu->isButtonPressed("Resume"))
    this->paused = !this->paused;
}

