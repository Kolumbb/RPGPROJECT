#include "Tile.hpp"


//Initializers
auto Tile::initCollisionBox() -> void {
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
    this->collisionBox.setSize(this->shape.getSize());
    this->collisionBox.setPosition(this->shape.getPosition());

}

//Constructors & Destructors
Tile::Tile(u_short x, u_short y, float gridSizeF, sf::Texture &texture, const sf::IntRect &intRect,
           const bool &collision, u_short type): collision(collision), type(type) {
    this->shape.setSize(sf::Vector2f (gridSizeF, gridSizeF));
    this->shape.setPosition(x * gridSizeF,y * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(intRect);
    this->initCollisionBox();
}

//Update methods
auto Tile::update() -> void {

}
//Render methods
auto Tile::render(sf::RenderTarget* target) -> void {
    target->draw(this->shape);
}

auto Tile::renderCollisionBox(sf::RenderTarget* target) -> void {
    if(this->getCollision()) target->draw(this->collisionBox);
}

//Other public methods
auto Tile::getTile() const -> const std::string {
    auto tileAsString = std::stringstream();
    tileAsString <<
                 std::to_string(this->shape.getTextureRect().left) << " " <<
                 std::to_string(this->shape.getTextureRect().top) << " " <<
                 std::to_string(this->collision) << " " << this->type;
    return tileAsString.str();
}
auto Tile::getPosition() const -> const sf::Vector2f & {
    return this->shape.getPosition();
}
auto Tile::getCollision() const -> const bool& {
    return this->collision;
}
auto Tile::intersects(const sf::FloatRect& floatRect) const -> const bool& {
    return this->shape.getGlobalBounds().intersects(floatRect);
}
auto Tile::getGlobalBounds() const -> const sf::FloatRect & {
    return sf::FloatRect (
            this->shape.getGlobalBounds().left,
            this->shape.getGlobalBounds().top,
            this->shape.getGlobalBounds().width ,
            this->shape.getGlobalBounds().height
            );
}



