//
// Created by Jakub Amerek on 25/03/2024.
//

#pragma once
#include "../ResourcePath.hpp"
#include "Gui.hpp"

class PlayerGui {
private:
    //Variables & Resources

    sf::RectangleShape healthBar;
    sf::RectangleShape healthAmount;
    sf::Vector2f size;
public:
    PlayerGui(const float &playerHealth, float sizeY);
    ~PlayerGui() = default;

    void update(const float& dt, const float& playerHealth);
    void render(sf::RenderTarget* target);

};


