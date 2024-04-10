#pragma once
#include "../Components/AnimationComponent.hpp"
#include "../Components/HitBoxComponent.hpp"
#include "../Components/MovementComponent.hpp"
#include "../ResourcePath.hpp"

class Entity {
private:
    my::Culling culling;






protected:
    //Variables & Resources
    std::unique_ptr<HitBoxComponent> hitboxComponent;
    std::unique_ptr<MovementComponent> movementComponent;
    std::unique_ptr<AnimationComponent> animationComponent;
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;
    bool playerAttack;
    bool playerHurt;
    int direction;
    float health;




    //Initializers
    virtual auto initMovementComp() -> void = 0;
    virtual auto initAnimationComp() -> void = 0;
    virtual auto initHitBoxComp() -> void = 0;
    virtual auto initTexture(const std::filesystem::path& path) -> void = 0;
    virtual auto initSprite(const sf::Vector2f& startPos) -> void = 0;
public:

    //Constructors & Destructors
    Entity(const float& health);
    virtual ~Entity();

    //Update methods
    virtual auto update(const float& dt) -> void = 0;
    auto updateDirection() -> void;
    //Render methods
    virtual auto render(std::shared_ptr<sf::RenderTarget> target) -> void = 0;

    //Other methods
    virtual auto move(const float& x, const float& y) -> void = 0;
    virtual auto stopVelocity() -> void;
    virtual auto stopVelocityX() -> void;
    virtual auto stopVelocityY() -> void;
    auto getAttack() const -> const bool&;
    auto getHealth() const -> const float&;

    //Accessors & Modifiers
    auto getPositionF() const -> const sf::Vector2f&;
    auto getGridPosition(const u_short& gridSizeU) const -> const sf::Vector2u&;
    auto getGlobalBounds() const -> const sf::FloatRect&;
    auto getNextPosition(const float&dt) const -> const sf::FloatRect&;
    auto setPosition(const float posX, const float posY) -> void;
    auto getCulling() -> my::Culling;
    auto setCullingToX(const int& val) -> void;
    auto setCullingToY(const int& val) -> void;
    auto setCullingFromX(const int& val) -> void;
    auto setCullingFromY(const int& val) -> void;

    virtual auto getDamage(const float& dt) -> void = 0;
};
