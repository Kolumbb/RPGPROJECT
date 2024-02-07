#pragma once
#include "../ResourcePath.hpp"
#include "../States/MainMenuState.hpp"
#include "../Gui/PauseMenu.hpp"
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
  std::shared_ptr<Player> player;
  std::shared_ptr<Slime> slime;

  std::shared_ptr<TileMap> map;

  // Accessors & Modifiers

  // Initializers
  auto initKeyBinds(const std::filesystem::path &path =
                        "../Resources/Config/key_binds_gamestate.ini") -> void;
  auto initPlayer();
  auto initSlime();
  auto initPausedMenu() -> void;
  auto initView() -> void;
  auto initBufferedRender() -> void;
  auto initTileMap() -> void;
  // Update methods
  auto update(const float &dt) -> void;
  auto updateButtons(const float &dt) -> void;
  auto updatePaused(const float &dt) -> void;
  auto updateUserInput(const float &dt) -> void;
  auto updateUnPaused(const float &dt) -> void;
  auto updateKeyBindsInput(const float &dt) -> void;
  auto updateView() -> void;

  auto updateTileMap(const float& dt) -> void;

  // Render methods
  auto render(sf::RenderTarget* target) -> void;
  auto renderPaused(sf::RenderTarget* target) -> void;
  auto renderUnPaused(sf::RenderTarget* target) -> void;

protected:
public:
  explicit GameState(StateData &state_data);
  ~GameState() = default;

};

