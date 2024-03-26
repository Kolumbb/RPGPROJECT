#pragma once
#include "../ResourcePath.hpp"
#include "../States/MainMenuState.hpp"
#include "../Gui/PauseMenu.hpp"
#include "../Gui/PlayerGui.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Slime.hpp"
#include "../Tile/TileMap.hpp"



class GameState :
    public State {
private:
  // Variables & Resources
  sf::View gameView;
  sf::RenderTexture renderTexture;
  sf::Sprite renderSprite;
  bool paused;
  std::unique_ptr<PauseMenu> pMenu;
  std::vector<std::shared_ptr<Entity>> entities;
  std::unique_ptr<TileMap> map;
  std::unique_ptr<PlayerGui> playerGui;

  // Accessors & Modifiers

  // Initializers
  auto initKeyBinds(const std::filesystem::path &path = "../Resources/Config/key_binds_gamestate.ini") -> void;
  auto initEntities() -> void;
  auto initPausedMenu() -> void;
  auto initView() -> void;
  auto initBufferedRender() -> void;
  auto initTileMap() -> void;
  auto initPlayerGui() -> void;
  // Update methods
  auto update(const float &dt) -> void;
  auto updateButtons(const float &dt) -> void;
  auto updatePaused(const float &dt) -> void;
  auto updateUserInput() -> void;
  auto updateUnPaused(const float &dt) -> void;
  auto updateKeyBindsInput(const float &dt) -> void;
  auto updateView() -> void;
  auto updateTileMap(const float& dt) -> void;
  auto updatePlayerHealth() -> void;

    // Render methods
  auto render(sf::RenderTarget* target) -> void;
  auto renderPaused(sf::RenderTarget* target) -> void;
  auto renderUnPaused(sf::RenderTarget* target) -> void;

protected:
public:
  explicit GameState(StateData &state_data);
  ~GameState() = default;
};

