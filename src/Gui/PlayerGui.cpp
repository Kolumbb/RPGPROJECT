#include "PlayerGui.hpp"


PlayerGui::PlayerGui(const float &playerHealth): size(sf::Vector2f(playerHealth, 30.f)) {

    this->healthBar.setPosition(30.f, 30.f);
    this->healthBar.setSize(this->size);
    this->healthBar.setOutlineThickness(1.f);
    this->healthBar.setOutlineColor(sf::Color::Black);
//    this->healthAmount.setSize(this->size);
//    this->healthAmount.setFillColor(sf::Color::Red);

}

void PlayerGui::update(const float &dt, const float& playerHealth) {
//    for(auto i = this->healthBar.getPosition().x ; i < this->healthBar.getPosition().x + this->size.x ; i++)
//        for(auto j = this->healthBar.getPosition().y ; j < this->healthBar.getPosition().y + this->size.x ; j++){
//            auto health = sf::Vector2f(playerHealth, this->size.y);
//            this->healthAmount.setSize(health);
//        }
}

void PlayerGui::render(sf::RenderTarget *target) {
    target->draw(this->healthBar);
    target->draw(this->healthAmount);
}
