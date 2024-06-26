#include "PlayerGui.hpp"


PlayerGui::PlayerGui(std::shared_ptr<Entity> player): player(player), size(sf::Vector2f(this->player->getHealth(), 30.f)) {

    this->healthBar.setPosition(50.f, 50.f);
    this->healthBar.setSize(this->size);
    this->healthBar.setFillColor(sf::Color::Black);
    this->healthAmount.setPosition(50.f, 50.f);
    this->healthAmount.setSize(sf::Vector2f (this->player->getHealth(), this->size.y));
    this->healthAmount.setFillColor(sf::Color::Red);
    this->healthAmount.setOutlineThickness(1.f);
    this->healthAmount.setOutlineColor(sf::Color::Black);


}

auto PlayerGui::update(const float &dt, std::shared_ptr<Entity> player) -> void{
    this->timer.updateKeyTime(dt);
    if(player->getHealth() != this->healthAmount.getSize().x)
        this->healthAmount.setSize(sf::Vector2f(player->getHealth(), this->healthBar.getSize().y));
}

auto PlayerGui::render(std::shared_ptr<sf::RenderTarget> target) -> void{
    target->draw(this->healthBar);
    target->draw(this->healthAmount);
}
