

#pragma once
#include "../ResourcePath.hpp"
#include "Entity.hpp"


class Slime : public Entity {
private:
  // Variables
  int limiter;

  // Initializers
  auto initTexture(const std::filesystem::path &path =
                       "../Resources/gameState/slime-Sheet.png") -> void;
  auto initSprite(const sf::Vector2f& startPos) -> void;
  auto initHitBoxComp() -> void;
  auto initMovementComp() -> void;
  auto initAnimationComp() -> void;

  // Private methods


protected:
public:
  // Constructors & Destructors
  Slime(const sf::Vector2f& startPos, const float& health);
  ~Slime() override;


  // Uprade methods
  auto update(const float &dt) -> void override;
  auto updateInputForAnimation(const float &dt) -> void;
  auto updateMovingPath() -> void;


  // Render methods
  auto render(std::shared_ptr<sf::RenderTarget> target) -> void override;

  // Other methods
  auto move(const float &x, const float &y) -> void;

  //Accessors & Modifiers
  auto  getDamage(const float& dt) -> void override;


};


