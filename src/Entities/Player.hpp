#pragma once

#include "Entity.hpp"
#include "../ResourcePath.hpp"

class Player : public Entity {
private:
  // Variables
  bool playerAttack;
  // Initializers
  auto initTexture(const std::filesystem::path &path =
                       "../Resources/gameState/adventurer-Sheet.png") -> void;
  auto initSprite() -> void;
  auto initHitboxComponent() -> void;
  auto initMovementComponent() -> void;
  auto initAnimationComponent() -> void;

  // Private methods
  auto animateAttack(const float &dt) -> void;
  auto animateJump(const float &dt) -> void;

protected:
public:
  // Constructors & Destructors
  Player();
  ~Player() = default;

  // Uprade methods
  auto update(const float &dt) -> void;
  auto updateInputForAnimation(const float &dt) -> void;

  // Render methods
  auto render(sf::RenderTarget* target) -> void;

  // Other methods
  auto move(const float &x, const float &y) -> void;
  auto jump(const float &x = 0.f, const float &y = -1.f) -> void;
  auto fall(const float &x = 0.f, const float &y = 1.f) -> void;

  //Accessors
  auto getAttack() const -> const bool&;



  //Modifiers
  auto setAttack() -> void;
  auto setJump() -> void;

};
