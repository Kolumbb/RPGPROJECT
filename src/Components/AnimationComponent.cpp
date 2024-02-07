#include "AnimationComponent.hpp"

//Constructors & Destructors





AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet):
    sprite(sprite), textureSheet(textureSheet),lastAnimation(nullptr), priorityAnimation(nullptr){

}

//Other public methods
auto AnimationComponent::addAnimation(
	const std::string& name, float animationTimer, 
	u_short startX, u_short startY, u_short endRectsX,
	u_short endRectsY, u_short width, u_short height
) -> void{
	this->animations[name] = std::make_shared<Animation>(this->sprite, this->textureSheet, animationTimer, startX, startY, endRectsX, endRectsY, width, height);
}

auto AnimationComponent::play(const std::string& name, const float& dt, const bool priority) -> const bool& {
		if (this->priorityAnimation) //If there is a priority animation
		{
			if (this->priorityAnimation == this->animations[name])
			{
				if (this->lastAnimation != this->animations[name])
				{
					if (this->lastAnimation == nullptr)
						this->lastAnimation = this->animations[name];
					else
					{
						this->lastAnimation->reset();
						this->lastAnimation = this->animations[name];
					}
				}

				//If the priority animation is done, remove it
				if (this->animations[name]->play(dt))
				{
					this->priorityAnimation = nullptr;
				}
			}
		}
		else //Play animation of no other priority animation is set
		{
			//If this is a priority animation, set it.
			if (priority)
			{
				this->priorityAnimation = this->animations[name];
			}

			if (this->lastAnimation != this->animations[name])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[name];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[name];
				}
			}
			this->animations[name]->play(dt);
		}
		return this->animations[name]->isDone();
	}


