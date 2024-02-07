#pragma once

#include "../ResourcePath.hpp"
#include "../Animation.hpp"

class AnimationComponent {
private:
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
public:
	//Getters

	//Constructors & Destructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	~AnimationComponent() = default;

	//Other public methods
	auto addAnimation(const std::string& name, float animationTimer, u_short startX, u_short startY,
                      u_short endRectsX, u_short endRectsY, u_short width, u_short height) -> void;

	auto play(const std::string& name, const float& dt, const bool priority = false) -> const bool&;
};
