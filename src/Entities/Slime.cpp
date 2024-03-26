#include "Slime.hpp"

//Initializers
auto Slime::initMovementComp() -> void {
  this->movementComponent = std::make_unique<MovementComponent>(
      *this->sprite, 100.f, 80.f, 58.f
  );
}

auto Slime::initAnimationComp() -> void{
  this->animationComponent = std::make_unique<AnimationComponent>(*this->sprite, *this->texture);
  this->animationComponent->addAnimation(
      "RUN", 90.f, 0, 0, 7, 0, 32, 25
  );


}

auto Slime::initTexture(const std::filesystem::path& path) -> void {
  this->texture->loadFromFile(path.string());
}

auto Slime::initSprite(const sf::Vector2f& startPos) -> void {
    this->sprite->setTexture(*this->texture);
    this->sprite->setScale(-2, 2);
    this->sprite->setOrigin(26.f, 0.f);
    this->sprite->setPosition(startPos);
}

auto Slime::initHitBoxComp() -> void{
  this->hitboxComponent = std::make_unique<HitBoxComponent>(*this->sprite, 0.f, 21.f, 35.f, 25.f);
}

//Constructors & Destructors
Slime::Slime(const sf::Vector2f& startPos, const float& health): Entity(health) {
  this->initTexture();
  this->initSprite(startPos);
  this->initHitBoxComp();
  this->initMovementComp();
  this->initAnimationComp();
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
    //this->updateMovingPath();


}

auto Slime::updateMovingPath() -> void {
    // Slime movements
    if (this->limiter < 200) {
        this->limiter++;
        this->movementComponent->move(this->direction * 2.f, 0);
    } else {
        this->direction *= -1;
        if(this->direction == -1)
            this->sprite->setOrigin(6.f, 0.f);
        else
            this->sprite->setOrigin(26.f, 0.f);

        this->sprite->setScale( this->direction * -2.f, 2.f);
        this->limiter = 0;
    }
}


auto Slime::render(sf::RenderTarget* target) -> void {
  target->draw(*this->sprite);
  this->hitboxComponent->render(target);
}

//Other methods
auto Slime::move(const float& x, const float& y) -> void {
  this->movementComponent->move(x, y);
}


