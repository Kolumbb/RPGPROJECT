#include "MovementComponent.hpp"


/*
	The idea of movement component is that we are taking an input from user in game state to move the entity sprite. By move function we are increasing the value of
	movement velocity by adding acceleration.
*/



//Constructors & Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& maxVelocity, const float& acceleration, const float& deceleration): 
	velocity(sf::Vector2f{0, 0}), sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {
}



//Update methods
void MovementComponent::update(const float& dt) {


	/*
		When none of buttons are pressed, force of deceleration decreses velocity, 
		so that the entity would not move in infinite time. Also creating bounds over 
		acceleration to keep velocity in check.
		At the end moves the sprite with the achieved velocity 
	*/

	//Left & Rignt bounds
	if (this->velocity.x > 0.f) {
		//Acceleration
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else {
		//Acceleration
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	//Up & Down bounds
    if (this->velocity.y > 0.f) {
        //Acceleration
        if (this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;

        //Deceleration
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;
    }
    else {
        //Acceleration
        if (this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;

        //Deceleration
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0.f;
    }
	

	this->sprite.move(this->velocity * dt);
}

//Other methods
void MovementComponent::move(const float& x, const float& y){
        this->velocity.x += this->acceleration * x;
        this->velocity.y += this->acceleration * y;
	//Increase velocity after button press
}

void MovementComponent::jump(const float& x, const float& y){
        this->velocity.x += (this->acceleration) * x;
        this->velocity.y += (this->acceleration) * y;

}

auto MovementComponent::fall(const float &x, const float &y) -> void {
  this->velocity.x += this->acceleration * x;
  this->velocity.y += (20*this->acceleration) * y;
}

auto MovementComponent::stopVelocity() -> void {
  this->velocity.x = 0.f;
  this->velocity.y = 0.f;
}

auto MovementComponent::stopVelocityX() -> void {
  this->velocity.x = 0.f;

}

auto MovementComponent::stopVelocityY() -> void {
  this->velocity.y = 0.f;

}

//Accessors & Modifiers
auto MovementComponent::getMaxVelocity() const -> const float& {
  return this->maxVelocity;
}

auto MovementComponent::isIdle() const-> const bool{
  if (this->velocity == sf::Vector2f(0, 0))
    return true;
  return false;
}

auto MovementComponent::checkDirection(Direction dir) const -> const bool{

  /*
          The idea is to check the direction given in the method
  */

  switch (dir) {
  case Direction::IDLE:
    if (this->velocity == sf::Vector2f(0.f, 0.f)) return true;
    break;

  case Direction::LEFT:
    if (this->velocity.x > 0.f) return true;
    break;

  case Direction::RIGHT:
    if (this->velocity.x < 0.f) return true;
    break;

  case Direction::JUMP:
    if (this->velocity.y < 0.f) return true;
    break;

  case Direction::FALL:
    if (this->velocity.y > 0.f) return true;
    break;
  }
  return false;
}

auto MovementComponent::getVelocity() const -> const sf::Vector2f&{
  return this->velocity;
}

