#include "HitBoxComponent.hpp"

//Initializers
auto HitBoxComponent::initHitBox(const float& width, const float& height) -> void {
  this->hitBox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y);
  this->hitBox.setSize(sf::Vector2f(width, height));

  this->hitBox.setFillColor(sf::Color::Transparent);
  this->hitBox.setOutlineColor(sf::Color::Red);
  this->hitBox.setOutlineThickness(1.f);
}


auto HitBoxComponent::initNextPosition(const float& width, const float& height) -> void {
  this->nextPosition = sf::FloatRect (0.f, 0.f, width, height);
}

//Constructors & Destructors
HitBoxComponent::HitBoxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height)
	: sprite(sprite), offsetX(offsetX), offsetY(offsetY){

  this->initHitBox(width, height);
  this->initNextPosition(width, height);

	
}


//Update methods
auto HitBoxComponent::update() -> void{
	this->hitBox.setPosition(
		this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY
	);
}

//Render methods
auto HitBoxComponent::render(std::shared_ptr<sf::RenderTarget> target) -> void {
	target->draw(this->hitBox);
}

//Other public methods
auto HitBoxComponent::intersects(const sf::FloatRect& fRect) -> bool{
	return this->hitBox.getGlobalBounds().intersects(fRect);
}


//Accessors & Modifiers
auto HitBoxComponent::getPosition() const -> const sf::Vector2f & {
  return this->hitBox.getPosition();
}

auto HitBoxComponent::setPosition(const float &posX, const float &posY)-> void {
  this->hitBox.setPosition(posX, posY);
  this->sprite.setPosition(
      posX - this->offsetX,
      posY - this->offsetY
  );

}
auto HitBoxComponent::getGlobalBounds() const-> const sf::FloatRect& {
  return this->hitBox.getGlobalBounds();
}
auto HitBoxComponent::getNextPosition(const sf::Vector2f &velocity)
    -> const sf::FloatRect& {

  this->nextPosition.left = this->hitBox.getPosition().x + velocity.x;
  this->nextPosition.top = this->hitBox.getPosition().y + velocity.y;
  return this->nextPosition;
}


