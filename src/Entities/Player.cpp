#include "Player.hpp"


//Initializers
auto Player::initMovementComp() -> void {
	this->movementComponent = std::make_unique<MovementComponent>(
            *this->sprite, 200.f, 80.f, 58.f
            );
}

auto Player::initAnimationComp() -> void{
    this->animationComponent = std::make_unique<AnimationComponent>(*this->sprite, *this->texture);
    this->animationComponent->addAnimation(
            "RUN", 90.f, 0, 1, 7, 1, 144, 96
            );
    this->animationComponent->addAnimation(
            "IDLE", 90.f, 0, 0, 15, 0, 144, 96
    );

    this->animationComponent->addAnimation(
            "HURT", 90.f, 0, 5, 7, 5, 144, 96
    );

}

auto Player::initTexture(const std::filesystem::path& path = "../Resources/gameState/warrior-all-animations.png") -> void {
	this->texture->loadFromFile(path.string());
}

auto Player::initSprite(const sf::Vector2f& startPos) -> void {
    this->sprite->setPosition(startPos);
    this->sprite->setTexture(*this->texture);
    this->sprite->setOrigin(72, 1);
    this->sprite->setScale(1,1);
}

auto Player::initHitBoxComp() -> void{
	this->hitboxComponent = std::make_unique<HitBoxComponent>(
                *this->sprite, -18.f, 25.f, 30.f, 45.f
                );
}



//Constructors & Destructors
Player::Player(const sf::Vector2f& startPos, const float& health): Entity(health) {
  this->initTexture();
  this->initSprite(startPos);
  this->initHitBoxComp();
  this->initMovementComp();
  this->initAnimationComp();
}

Player::~Player() {
    std::cout <<"Player deleted" << std::endl;
}

//Update methods
auto Player::update(const float& dt) -> void {
	this->movementComponent->update(dt);
	this->updateInputForAnimation(dt);
	this->hitboxComponent->update();
        this->updateDirection();
}

auto Player::updateInputForAnimation(const float& dt) -> void{
    if (this->playerAttack) {
        this->animateAttack(dt);
    }
    else {
        if (this->movementComponent->checkDirection(Direction::IDLE)) {
            this->animationComponent->play("IDLE", dt);
        }
        else if (this->movementComponent->checkDirection(Direction::LEFT)) {
            this->sprite->setScale(this->direction,1);
            this->animationComponent->play("RUN", dt);
        }

        else if (this->movementComponent->checkDirection(Direction::RIGHT)) {
            this->sprite->setScale(this->direction,1);
            this->animationComponent->play("RUN", dt);
        }
        else if (this->movementComponent->checkDirection(Direction::UP)) {
            this->animationComponent->play("RUN", dt);
        }
        else if (this->movementComponent->checkDirection(Direction::DOWN)) {
            this->animationComponent->play("RUN", dt);
        }
    }
}
		

auto Player::render(std::shared_ptr<sf::RenderTarget> target) -> void {
    target->draw(*this->sprite);
    this->hitboxComponent->render(target);


}

//Other methods
auto Player::move(const float& x, const float& y) -> void {
	this->movementComponent->move(x, y);
}



auto Player::animateAttack(const float& dt) -> void {
  if (this->animationComponent->play("ATTACK1", dt, true)) {
    this->setAttack();
  }
}



//Accessors



//Modifiers
auto Player::setAttack() -> void{
  if (this->playerAttack)
    this->playerAttack = false;
  else this->playerAttack = true;
}

auto Player::getDamage() -> void {
    this->health -= 10;
}






