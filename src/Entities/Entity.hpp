#pragma once
#include "../Components/AnimationComponent.hpp"
#include "../Components/HitBoxComponent.hpp"
#include "../Components/MovementComponent.hpp"
#include "../ResourcePath.hpp"

class Entity {
protected:
	//Variables & Resources
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<MovementComponent> movementComponent;
	std::shared_ptr<AnimationComponent> animationComponent;
        Entities entity;
        bool playerJump;




	//Initializers
	virtual auto initMovementComponent() -> void = 0;
	virtual auto initAnimationComponent() -> void = 0;
	virtual auto initHitboxComponent() -> void = 0;
	virtual auto initTexture(const std::filesystem::path& path) -> void = 0;
	virtual auto initSprite() -> void = 0;
public:
    std::shared_ptr<HitBoxComponent> hitboxComponent;

    //Constructors & Destructors
	Entity(Entities entitiy = Entities::Hero);
	virtual ~Entity() = default;

	//Update methods
	virtual auto update(const float& dt) -> void = 0;

	//Render methods
	virtual auto render(sf::RenderTarget* target) -> void = 0;

	//Other methods
	virtual auto move(const float& x, const float& y) -> void = 0;
        virtual auto stopVelocity() -> void;
        virtual auto stopVelocityX() -> void;
        virtual auto stopVelocityY() -> void;
        auto identifyEntity() const -> const Entities;

        //Accessors & Modifiers
        auto getPositionF() const -> const sf::Vector2f&;
        auto getGridPosition(const u_short& gridSizeU) const -> const sf::Vector2u&;
        auto getGlobalBounds() const -> const sf::FloatRect&;
        auto getJump() const -> const bool&;
        auto getNextPosition(const float&dt) const -> const sf::FloatRect&;
        auto setPosition(const float posX, const float posY) -> void;
        auto isIdle() const -> const bool&;


};
