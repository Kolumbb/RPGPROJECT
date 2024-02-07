#include "Slime.hpp"

//Initializers
auto Slime::initMovementComponent() -> void {
  this->movementComponent = std::make_shared<MovementComponent>(
      *this->sprite, 100.f, 80.f, 58.f
  );
}

auto Slime::initAnimationComponent() -> void{
  this->animationComponent = std::make_shared<AnimationComponent>(*this->sprite, *this->texture);
  this->animationComponent->addAnimation(
      "RUN", 90.f, 0, 0, 7, 0, 32, 25
  );


}

auto Slime::initTexture(const std::filesystem::path& path) -> void {
  this->texture->loadFromFile(path.string());
}

auto Slime::initSprite() -> void {
  this->sprite->setTexture(*this->texture);
  this->sprite->setScale(-2, 2);
  this->sprite->setPosition(1100.f, 200.f);
}

auto Slime::initHitboxComponent() -> void{
  this->hitboxComponent = std::make_shared<HitBoxComponent>(*this->sprite, -42.f, 21.f, 32.f, 25.f);
}

//Constructors & Destructors
Slime::Slime(Entities entity): limiter(0), direction(1) {
  this->initTexture();
  this->initSprite();
  this->initHitboxComponent();
  this->initMovementComponent();
  this->initAnimationComponent();
}

//Update methods
auto Slime::update(const float& dt) -> void {
  this->movementComponent->update(dt);
  this->updateInputForAnimation(dt);
  this->hitboxComponent->update();
}

auto Slime::updateInputForAnimation(const float& dt) -> void {
  if (this->movementComponent->checkDirection(Direction::LEFT) ||
      this->movementComponent->checkDirection(Direction::RIGHT)) {
    this->animationComponent->play("RUN", dt);
  }

  // Slime movements
  if (!this->movementComponent->checkDirection(Direction::FALL)) {


    if (limiter < 200) {
      limiter++;
      this->movementComponent->move(this->direction, 0);
    } else {


      this->sprite->setOrigin(this->direction * 18.f, 0.f);
      this->sprite->setScale(this->direction * 2.f, 2.f);
      this->direction = -this->direction;
      limiter = 0;
    }
  }


}


auto Slime::render(sf::RenderTarget* target) -> void {
  target->draw(*this->sprite);
  //this->hitboxComponent->render(target);
}

//Other methods
auto Slime::move(const float& x, const float& y) -> void {
  this->movementComponent->move(x, y);
}

auto Slime::fall(const float &x, const float &y) -> void {
  this->movementComponent->fall(x, y);
}