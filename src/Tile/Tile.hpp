#pragma once

#include "../ResourcePath.hpp"


class Tile {
private:
    //Variables & Resources
    sf::RectangleShape shape;
    bool collision;
    u_short type;
protected:
public:
    //Constructors & Destructors
    Tile(u_short x, u_short y, float gridSizeF, sf::Texture& texture,
         const sf::IntRect& intRect, const bool& collision = false, u_short type = TileType::DEFAULT
    );
    ~Tile() = default;

    //Update methods
    auto update() -> void;

    //Render methods
    auto render(sf::RenderTarget* target) -> void;

    //Other public methods
    auto intersects(const sf::FloatRect& floatRect) const -> const bool&;
    //Accessors & Modifiers
    auto getTile() const ->const std::string;
    auto getPosition() const -> const sf::Vector2f&;
    auto getCollision() const  -> const  bool&;
    auto getGlobalBounds() const -> const sf::FloatRect&;

};

