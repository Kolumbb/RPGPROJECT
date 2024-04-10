#include "EditorState.hpp"

//Initializers
auto EditorState::initBackground(const std::filesystem::path& path) -> void {

}

auto EditorState::initKeyBinds(const std::filesystem::path& path)-> void {

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


auto EditorState::initPausedMenu() -> void {
    this->pMenu = std::make_unique<PauseMenu>(this->stateData, 150, 16);
}

auto EditorState::initTileMap() -> void {
    this->tileMap = std::make_unique<TileMap>(this->stateData.gridSizeF, 150, 50);
}

auto EditorState::initGui() -> void {
    this->textureSelector = std::make_unique<gui::TextureSelector>(32.f, 32.f, 896.f, 512.f,this->stateData.gridSizeF, *this->tileMap->getTexture(), this->stateData);

    this->selector.setSize(sf::Vector2f (this->stateData.gridSizeF,this->stateData.gridSizeF));
    this->selector.setFillColor(sf::Color(255, 255, 255, 150));
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Green);
    this->selector.setTexture(this->tileMap->getTexture().get());
    this->selector.setTextureRect(sf::IntRect (32, 32, this->stateData.gridSizeF, this->stateData.gridSizeF));

    this->sideBar = std::make_unique<sf::RectangleShape>();
    this->sideBar->setSize(sf::Vector2f (static_cast<float>(this->stateData.gfxSettings->resolution.width), this->stateData.gridSizeF - 1.f));
    this->sideBar->setPosition(sf::Vector2f ());
    this->sideBar->setFillColor(sf::Color(70, 70, 70, 255));
    this->sideBar->setOutlineThickness(1.f);
    this->sideBar->setOutlineColor(sf::Color(255, 255, 255, 200));

    auto gWidth = stateData.gfxSettings->resolution.width;
    this->texturePack = std::make_unique<gui::Button>(
        0, //pos_x
        0, //pos_y
        this->stateData.gridSizeF - 1.f, //width
        this->stateData.gridSizeF - 1.f, //height
        "TS1", gWidth/ 80.f,
        sf::Color(255, 255, 255, 255),
        sf::Color(250, 250, 250, 250),
        sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 255),
        sf::Color(150, 150, 150, 0),
        sf::Color(20, 20, 20, 0), stateData.font
    );
}

auto EditorState::initMouseText() -> void {
    this->mouseText.setFillColor(sf::Color::White);
    this->mouseText.setFont(this->stateData.font);
    this->mouseText.setCharacterSize(12);
    this->mouseText.setString(std::to_string(this->collision) + "\n" + std::to_string(this->layer));
    this->mouseText.setPosition(this->mousePosWindow.x + 5.f, this->mousePosWindow.y + 5.f);
}


auto EditorState::initView() -> void {
    this->gameView.setSize(
            sf::Vector2f(
                    this->stateData.gfxSettings->resolution.width,
                    this->stateData.gfxSettings->resolution.height
                )
            );
    this->gameView.setCenter(
            sf::Vector2f (
                    this->stateData.gfxSettings->resolution.width / 2.f,
                    this->stateData.gfxSettings->resolution.height / 2.f
            )
    );
}

//Constructors & Destructors
EditorState::EditorState(StateData& stateData, bool collision, u_short type) :
        State(stateData), paused(false), collision(collision), layer(0),cameraSpeed(10.f), texturePackActive(false) {

    this->initKeyBinds();
    this->initPausedMenu();
    this->initBackground();
    this->initTileMap();
    this->initGui();
    this->initMouseText();
    this->initView();
}



//Update methods
auto EditorState::update(const float& dt) -> void {
    this->timer.updateKeyTime(dt);
    this->updateMousePos(this->gameView);
    this->updateKeyBindsInput(dt);

    this->texturePack->update(dt, mousePosWindow);

    if(this->texturePack->isPressed() && timer.getKeyTime()){
      if(!this->texturePackActive) this->texturePackActive = true;
      else this->texturePackActive = false;
    }
    if(this->texturePackActive) {
      if (this->textureSelector->getBounds(this->mousePosWindow)) this->textureSelector->setActive(true);
      else this->textureSelector->setActive(false);

      if(this->textureSelector->getActive()) this->textureSelector->update(this->mousePosU);


    }


    //Update unpaused
    if(!this->paused){
        this->updateUnPaused(dt);
    }
        //Update paused
    else {
        this->updatePaused(dt);
    }

}



auto EditorState::updateButtons(const float &dt) -> void {
    if(this->pMenu->isButtonPressed("Save") && this->timer.getKeyTime()) this->tileMap->saveMapToFile();
    else if(this->pMenu->isButtonPressed("Load") && this->timer.getKeyTime()) {
        this->tileMap->loadMapFromFile();
        this->initGui();
    }
    else if(this->pMenu->isButtonPressed("Resume") && this->timer.getKeyTime()) this->paused = false;
    else if(this->pMenu->isButtonPressed("Quit") && this->timer.getKeyTime()) this->stateData.states.pop();
}

auto EditorState::updatePaused(const float &dt) -> void {
    this->pMenu->update(dt, this->mousePosWindow);
        this->updateButtons(dt);

}

auto EditorState::updateUnPaused(const float &dt) -> void {
    this->updateEditorInput(dt);
    this->updateGui();
}

auto EditorState::updateKeyBindsInput(const float &dt) -> void {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["RIGHT"]))) this->gameView.move(this->cameraSpeed,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["LEFT"]))) this->gameView.move(-this->cameraSpeed,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["UP"]))) this->gameView.move(0.f,-this->cameraSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["DOWN"]))) this->gameView.move(0.f,this->cameraSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["ROTATE_RIGHT"])) && this->timer.getKeyTime())






    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["ROTATE_LEFT"]))) ;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CLOSE"])) && this->timer.getKeyTime()){
        this->paused = !this->paused;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["COLLISION"])) && this->timer.getKeyTime()){
        if(!this->collision) this->collision = true;
        else this->collision = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["INCREASE_TYPE"])) && this->timer.getKeyTime()){
        if(this->layer > 5) this->layer = 0;
        else this->layer++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["DECREASE_TYPE"])) && this->timer.getKeyTime()){
        if(this->layer >= 0) this->layer = 0;
        else this->layer--;
    }


}

auto EditorState::updateGui() -> void {
    this->selector.setPosition(
      this->mousePosGrid.x * this->stateData.gridSizeF,
      this->mousePosGrid.y * this->stateData.gridSizeF
      );

    this->mouseText.setString(std::to_string(this->collision) + "\n" + std::to_string(this->layer));
    this->mouseText.setPosition(this->mousePosWindow.x + 8.f, this->mousePosWindow.y + 8.f);

}

auto EditorState::updateEditorInput(const float &dt) -> void {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(this->textureSelector->getActive()){
            this->selector.setTextureRect(this->textureSelector->getInternalRect());
        }else{
            this->tileMap->addTile(
                    this->mousePosGrid.x , this->mousePosGrid.y,this->layer,this->selector.getTextureRect(), this->collision, TileType::DEFAULT
                    );
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, this->layer);
    }
}

//Render methods
auto EditorState::render(std::shared_ptr<sf::RenderTarget> target) -> void {
    this->renderUnPaused(target);
    if (this->paused)
        this->renderPaused(target);

}

auto EditorState::renderPaused(std::shared_ptr<sf::RenderTarget> target) -> void {
  target->setView(this->stateData.window->getDefaultView());
  this->pMenu->render(target);
}

auto EditorState::renderUnPaused(std::shared_ptr<sf::RenderTarget> target) -> void {
  target->setView(this->gameView);
  this->tileMap->render(target);
  this->tileMap->renderCollisionBox(target);
  this->renderGui(target);
}

auto EditorState::renderGui(std::shared_ptr<sf::RenderTarget> target) -> void {

  if(!this->textureSelector->getActive()) target->draw(this->selector);
  target->setView(this->stateData.window->getDefaultView());
  if(this->texturePackActive){

    this->textureSelector->render(target);
  }
  target->draw(this->mouseText);
  target->draw(*this->sideBar);
  this->texturePack->render(target);







}

