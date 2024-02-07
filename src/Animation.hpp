#pragma once

#include "ResourcePath.hpp"

class Animation {
private:
	//Variables & Resources
	sf::Texture& textureSheet;
	sf::Sprite& sprite;
	float animationTimer;
	float timer;
	sf::IntRect startRect;
	sf::IntRect endRect;
	sf::IntRect currentRect;
	u_short width;
	u_short height;
	bool done;

	//Initializers
	auto setSprite() -> void;

public:
	//Constructors & Destructors
	Animation(
		sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer,
		u_short startX, u_short startY, u_short endRectsX,
		u_short endRectsY, u_short width, u_short height
	);
	virtual ~Animation() = default;

	//Other public methods
    auto play(const float& dt) -> const bool&;
    auto reset() -> void;
	auto isDone() const -> const bool&;

};

