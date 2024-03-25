#include "Entity.hpp"



//Constructors & Destructors
Entity::Entity(): playerAttack(false), direction(1){
	this->texture = std::make_shared<sf::Texture>();
	this->sprite = std::make_shared<sf::Sprite>();
}

//Other public methods
auto Entity::stopVelocity() -> void {
  this->movementComponent->stopVelocity();
}
auto Entity::stopVelocityX() -> void {
  this->movementComponent->stopVelocityX();
}
auto Entity::stopVelocityY() -> void {
  this->movementComponent->stopVelocityY();
}


//Accessors & Modifiers
auto Entity::getPositionF() const -> const sf::Vector2f& {
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();

    return this->sprite->getPosition();
}

auto Entity::getGridPosition(const u_short& gridSizeU) const -> const sf::Vector2u& {
    if(this->hitboxComponent)
        return sf::Vector2u (
                static_cast<u_short>(this->hitboxComponent->getPosition().x) / gridSizeU,
                static_cast<u_short>(this->hitboxComponent->getPosition().y)/ gridSizeU
                );

    return sf::Vector2u (
      static_cast<u_short>(this->sprite->getPosition().x) / gridSizeU,
      static_cast<u_short>(this->sprite->getPosition().y) / gridSizeU
  );
}

auto Entity::getGlobalBounds() const -> const sf::FloatRect& {
  if(this->hitboxComponent)
    return this->hitboxComponent->getGlobalBounds();

  return this->sprite->getGlobalBounds();
}

auto Entity::setPosition(const float posX, const float posY) -> void {
  if(this->hitboxComponent)
    this->hitboxComponent->setPosition(posX, posY);
  else
    this->sprite->setPosition(posX, posY);
}

auto Entity::getNextPosition(const float& dt) const -> const sf::FloatRect & {
  if (this->hitboxComponent && this->movementComponent)
    return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

  return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}



auto Entity::updateDirection() -> void {
    if(this->movementComponent->getVelocity().x < 0.0f)
        this->direction = -1;
    else if(this->movementComponent->getVelocity().x > 0.0f)
        this->direction = 1;
}

auto Entity::getAttack() const -> const bool & {
    return this->playerAttack;
}

auto Entity::getCulling() -> my::Culling {
    return this->culling;
}

auto Entity::setCullingToX(const int &val) -> void {
    this->culling.toX = val;
}

auto Entity::setCullingToY(const int &val) -> void {
    this->culling.toY = val;
}

auto Entity::setCullingFromX(const int &val) -> void {
    this->culling.fromX = val;
}

auto Entity::setCullingFromY(const int &val) -> void {
    this->culling.fromY = val;
}



