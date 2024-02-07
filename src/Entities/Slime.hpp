

#pragma once
#include "../ResourcePath.hpp"
#include "Entity.hpp"


class Slime : public Entity {
private:
  // Variables


  // Initializers
  auto initTexture(const std::filesystem::path &path =
                       "../Resources/gameState/slime-Sheet.png") -> void;
  auto initSprite() -> void;
  auto initHitboxComponent() -> void;
  auto initMovementComponent() -> void;
  auto initAnimationComponent() -> void;

  // Private methods


protected:
public:
  // Constructors & Destructors
  Slime(Entities entity = Entities::Slime);
  ~Slime() = default;
  int limiter;
  int direction;

  // Uprade methods
  auto update(const float &dt) -> void;
  auto updateInputForAnimation(const float &dt) -> void;

  // Render methods
  auto render(sf::RenderTarget* target) -> void;

  // Other methods
  auto move(const float &x, const float &y) -> void;

  auto fall(const float &x = 0.f, const float &y = 1.f) -> void;



};


