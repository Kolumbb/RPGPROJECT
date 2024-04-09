#include "PlayerGui.hpp"


PlayerGui::PlayerGui(std::shared_ptr<Entity> player): player(player), size(sf::Vector2f(this->player->getHealth(), 30.f)) {

    this->healthBar.setPosition(50.f, 50.f);
    this->healthBar.setSize(this->size);
    this->healthBar.setFillColor(sf::Color::Black);
    this->healthAmount.setPosition(50.f, 50.f);
    this->healthBar.setSize(sf::Vector2f (this->player->getHealth(), this->size.y));
    this->healthBar.setFillColor(sf::Color::Red);
    this->healthBar.setOutlineThickness(1.f);
    this->healthBar.setOutlineColor(sf::Color::Black);


}

void PlayerGui::update(const float &dt, std::shared_ptr<Entity> player) {
    if(player->getHealth() != this->healthBar.getSize().x)
        this->healthBar.setSize(sf::Vector2f(player->getHealth(), this->healthBar.getSize().y));
}

void PlayerGui::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->healthBar);
    target->draw(this->healthAmount);
}
