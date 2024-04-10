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
    my::Timer timer;
    std::shared_ptr<Entity> player;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthAmount;
    sf::Vector2f size;
public:
    PlayerGui(std::shared_ptr<Entity> player);
    ~PlayerGui() = default;

    auto update(const float& dt, std::shared_ptr<Entity> player) -> void;

    auto render(std::shared_ptr<sf::RenderTarget> target) -> void;

};


