#include "ResourcePath.hpp"
//

// Created by Jakub Amerek on 03/01/2024.
//
auto my::splitTextByLetter(const std::string& text, char letter) -> std::pair<std::string, std::string> {
    size_t pos = text.find(letter);  // Find the position of the first occurrence of 'x'

    if (pos == std::string::npos) {
        return {text, ""};  // Return the original text if 'x' is not found
    }

    return {text.substr(0, pos), text.substr(pos + 1)};  // Split the text at 'x'
}
my::Timer::Timer(float keyTime, float keyTimeMax): keyTime(keyTime), keyTimeMax(keyTimeMax){}
auto my::Timer::getKeyTime() -> bool const {
    if (this->keyTime > this->keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

auto my::Timer::updateKeyTime(const float& dt) -> void {
    this->keyTime += 10 * dt;
}
my::Culling::Culling(int formX, int toX, int fromY, int toY, int layer)
    :fromX(fromX), toX(toX), fromY(fromY), toY(toY), layer(layer){};