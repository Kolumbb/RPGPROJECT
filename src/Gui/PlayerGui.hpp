//
// Created by Jakub Amerek on 25/03/2024.
//

#pragma once
#include "../ResourcePath.hpp"
#include "../Entities/Player.hpp"
#include "Gui.hpp"

class PlayerGui {
private:
    //Variables & Resources
    std::shared_ptr<Entity> player;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthAmount;
    sf::Vector2f size;
public:
    PlayerGui(std::shared_ptr<Entity> player);
    ~PlayerGui() = default;

    void update(const float& dt, std::shared_ptr<Entity> player);
    void render(std::shared_ptr<sf::RenderTarget> target);

};


