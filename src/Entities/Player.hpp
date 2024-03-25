#pragma once

#include "Entity.hpp"
#include "../ResourcePath.hpp"
#include "../Gui/PlayerGui.h"

class Player : public Entity {
private:
  // Variables
  std::unique_ptr<PlayerGui> playerGui;
  float health;
  // Initializers
  auto initTexture(const std::filesystem::path &path) -> void override;
  auto initSprite(const sf::Vector2f& startPos) -> void override;
  auto initHitBoxComp() -> void override;
  auto initMovementComp() -> void override;
  auto initAnimationComp() -> void override;
  auto initPlayerGui() -> void;

  // Private methods
  auto animateAttack(const float &dt) -> void;

protected:
public:
  // Constructors & Destructors
  Player(const sf::Vector2f& startPos);
  ~Player() override = default;

  // Uprade methods
  auto update(const float &dt) -> void override;
  auto updateInputForAnimation(const float &dt) -> void;

  // Render methods
  auto render(sf::RenderTarget* target) -> void override;

  // Other methods
  auto move(const float &x, const float &y) -> void override;


  //Accessors



  //Modifiers
  auto setAttack() -> void;

};
