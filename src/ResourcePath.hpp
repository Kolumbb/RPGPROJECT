////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2023 Marco Antognini (antognini.marco@gmail.com),
//                         Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef RESOURCE_PATH_HPP
#define RESOURCE_PATH_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Core
#include <memory>
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <list>
#include <map>
#include <cmath>
#include <filesystem>

class State;
typedef unsigned short u_short;
enum class Direction { IDLE = 0, LEFT, RIGHT, UP, DOWN };
enum class Destination {MAINMENU = 0, GAME, SETTINGS};
enum TileType {DEFAULT = 0, LAVA, GRASS, WATER, ICE};
enum class Entities{Hero = 0, Slime = 1};
namespace my {

struct Timer {
    float keyTime;
    float keyTimeMax;

    Timer(float keyTime = 0.f, float keyTimeMax = 1.f);
    ~Timer() = default;

    auto updateKeyTime(const float &dt) -> void;
    auto getKeyTime() -> bool const;
};

struct Culling {
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;
    Culling(int formX = 0, int toX = 0, int fromY = 0, int toY = 0,
          int layer = 3);
    ~Culling() = default;

};
auto splitTextByLetter(const std::string &text, char letter)
    -> std::pair<std::string, std::string>;
}


#endif
