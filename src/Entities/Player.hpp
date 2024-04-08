#pragma once

#include "Entity.hpp"
#include "../ResourcePath.hpp"

class Player : public Entity {
private:
  // Variables

  // Initializers
  auto initTexture(const std::filesystem::path &path) -> void override;
  auto initSprite(const sf::Vector2f& startPos) -> void override;
  auto initHitBoxComp() -> void override;
  auto initMovementComp() -> void override;
  auto initAnimationComp() -> void override;

  // Private methods
  auto animateAttack(const float &dt) -> void;

protected:
public:
  // Constructors & Destructors
  Player(const sf::Vector2f& startPos, const float& health);
  ~Player() override;

  // Uprade methods
  auto update(const float &dt) -> void override;
  auto updateInputForAnimation(const float &dt) -> void;

  // Render methods
  auto render(std::shared_ptr<sf::RenderTarget> target) -> void override;

  // Other methods
  auto move(const float &x, const float &y) -> void override;


  //Accessors


  //ModifiersŚ
  auto setAttack() -> void;

};
