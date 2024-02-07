#include "Player.hpp"



//Initializers
auto Player::initMovementComponent() -> void {
	this->movementComponent = std::make_shared<MovementComponent>(
            *this->sprite, 200.f, 80.f, 58.f
            );
}

auto Player::initAnimationComponent() -> void{
	this->animationComponent = std::make_shared<AnimationComponent>(*this->sprite, *this->texture);
	this->animationComponent->addAnimation(
            "RUN", 90.f, 0, 22, 5, 22, 50, 37
            );
	this->animationComponent->addAnimation(
            "ATTACK1", 100.f, 0, 6, 3, 6, 50, 37
            );
    this->animationComponent->addAnimation(
            "JUMP_PREPARE", 180.f, 0, 20, 1, 20, 50, 37
    );
    this->animationComponent->addAnimation(
            "JUMP_LAUNCH", 990.f, 1, 20, 2, 20, 50, 37
    );
    this->animationComponent->addAnimation(
            "JUMP_END", 990.f, 2, 20, 3, 20, 50, 37
    );
    this->animationComponent->addAnimation(
            "IDLE", 180.f, 0, 17, 3, 17, 50, 37
    );

}

auto Player::initTexture(const std::filesystem::path& path) -> void {
	this->texture->loadFromFile(path.string());
}

auto Player::initSprite() -> void {
  this->sprite->setTexture(*this->texture);
  this->sprite->setScale(2, 2);
  this->sprite->setPosition(200.f, 500.f);
}

auto Player::initHitboxComponent() -> void{
	this->hitboxComponent = std::make_shared<HitBoxComponent>(*this->sprite, 38.f, 21.f, 30.f, 50.f);
}

//Constructors & Destructors
Player::Player(): playerAttack(false) {
  this->initTexture();
  this->initSprite();
  this->initHitboxComponent();
  this->initMovementComponent();
  this->initAnimationComponent();
}

//Update methods
auto Player::update(const float& dt) -> void {
	this->movementComponent->update(dt);
	this->updateInputForAnimation(dt);
	this->hitboxComponent->update();
}

auto Player::updateInputForAnimation(const float& dt) -> void{
	if (this->playerAttack) {
		this->animateAttack(dt);
    }
    if (this->playerJump) {
            this->animateJump(dt);
    }
	else {
		if (this->movementComponent->checkDirection(Direction::IDLE)) {
			this->animationComponent->play("IDLE", dt);
		}

		else if (this->movementComponent->checkDirection(Direction::LEFT)) {
			this->sprite->setOrigin(0.f, 0.f);
			this->sprite->setScale(2.f, 2.f);
			this->animationComponent->play("RUN", dt);
		}

		else if (this->movementComponent->checkDirection(Direction::RIGHT)) {
			this->sprite->setOrigin(52.f, 0.f);
			this->sprite->setScale(-2.f, 2.f);
			this->animationComponent->play("RUN", dt);
		}
		else if (this->movementComponent->checkDirection(Direction::FALL)) {
			this->animationComponent->play("JUMP_END", dt);
		}
	}
}
		

auto Player::render(sf::RenderTarget* target) -> void {
	target->draw(*this->sprite);
	//this->hitboxComponent->render(target);
}

//Other methods
auto Player::move(const float& x, const float& y) -> void {
	this->movementComponent->move(x, y);
}

auto Player::jump(const float &x, const float &y) -> void {
    this->movementComponent->jump(x, y);
}

auto Player::animateAttack(const float& dt) -> void {
  if (this->animationComponent->play("ATTACK1", dt, true)) {
    this->setAttack();
  }
}

auto Player::animateJump(const float& dt) -> void {
  if (this->animationComponent->play("JUMP_PREPARE", dt, true)) {
    this->jump();
    if (this->animationComponent->play("JUMP_LAUNCH", dt, true)) {
        this->setJump();


    }
  }
}

//Accessors
auto Player::getAttack() const ->const bool& {
    return this->playerAttack;
}



//Modifiers
auto Player::setAttack() -> void{
  if (this->playerAttack)
    this->playerAttack = false;
  else this->playerAttack = true;
}

auto Player::setJump() -> void {
    if (this->playerJump)
        this->playerJump = false;
    else this->playerJump = true;
}
auto Player::fall(const float &x, const float &y) -> void {
  this->movementComponent->fall(x, y);
}


