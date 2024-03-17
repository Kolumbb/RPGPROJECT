#pragma once
#include "../ResourcePath.hpp"

class MovementComponent{
private:
	
	//Variables & Resources
	sf::Sprite& sprite;
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


public:
	MovementComponent(sf::Sprite& sprite, const float& maxVelocity, const float& acceleration, const float& deceleration);
	~MovementComponent() = default;

        //Update methods
        void update(const float& dt);

        //Other methods
        auto move(const float& x, const float& y) -> void;
        auto stopVelocity() -> void;
        auto stopVelocityX() -> void;
        auto stopVelocityY() -> void;

	//Accessors & Modifiers
	auto getMaxVelocity() const-> const float&;
	auto isIdle() const -> const bool;
	auto checkDirection(Direction dir) const -> const bool;
	auto getVelocity() const -> const sf::Vector2f&;



};

