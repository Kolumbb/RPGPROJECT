#include "Animation.hpp"

//Initializers
auto Animation::setSprite() -> void{
    this->sprite.setTexture(this->textureSheet, true);
    this->sprite.setTextureRect(this->currentRect);
}

//Constructors & Destructors

Animation::Animation(
	sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer,
	u_short startX, u_short startY, u_short endRectsX,
	u_short endRectsY, u_short width, u_short height
): textureSheet(textureSheet), sprite(sprite), animationTimer(animationTimer),width(width), height(height), done(false), timer(0.f){
	this->startRect = sf::IntRect(startX * width, startY * height, width, height);
	this->currentRect = startRect;
	this->setSprite();
	this->endRect = sf::IntRect(endRectsX * width, endRectsY * height, width, height);
	
	
}



/*
	What it basically does is increasing value of timer until it reach animationTimer that
	is determined for this specific animation - by that I am telling it how fast it would take
	to move int rect by a step closer to endRect. When it reach this time it will reset the timer
	and checks if it has the same value that end rect. If it is the same then reset current rect
	position of it.
*/

//Other public methods
auto Animation::play(const float& dt) -> const bool& {
    this->done = false;
    this->timer += 800.f * dt;
    if (this->timer >= this->animationTimer) {
        this->timer = 0.f;
        if (this->currentRect != this->endRect) { // Animate
            this->currentRect.left += this->width;
        }
        else { //Reset
            this->currentRect = this->startRect;
            this->done = true;
        }
        this->sprite.setTextureRect(this->currentRect);
    }
    return done;
}

auto Animation::reset() -> void {
    this->currentRect = this->startRect;
    this->timer = this->animationTimer;
}

auto Animation::isDone() const -> const bool&{
    return this->done;
}

