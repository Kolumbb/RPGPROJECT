#pragma once

#include "ResourcePath.hpp"
/*
	GFXSettings is a container with all graphical settings of the game. Class includes load and save methods
	that gives the user posibility to change it in settings state.
*/
struct GFXSettings {
    //Variables & Resources
    std::string title;
    sf::VideoMode resolution;
    bool fullScreen;
    bool verticalSync;
    unsigned int frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;


    //Constructors & Destructors
    GFXSettings();
    ~GFXSettings() = default;
    //Public methods
    void saveToFile(const std::filesystem::path& path = "../Resources/Config/display_settings.ini");
    void loadGraphicsFromFile(const std::filesystem::path& path = "../Resources/Config/display_settings.ini");
};

/*
	StateData is a container for state system resources. Contains the most important resources that the state system
	requiers for running.
*/

class StateData {
private:
    //Initializers
    auto initFont(const std::filesystem::path& path = "../Resources/Fonts/OpenSans-Regular.ttf") -> void;

    auto initSupportedKeys(const std::filesystem::path& path = "../Resources/config/supported_keys.ini") -> void;

    auto initWindow() -> void;

    auto initGFXSettings() -> void;


public:
    //Variables & Resources
	
    std::stack<std::shared_ptr<State>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::map<std::string, int> supportedKeys;
    std::shared_ptr <GFXSettings> gfxSettings;
    sf::Font font;
    float gridSizeF;

	
    //Constructors & Destructors
    StateData();
    ~StateData() = default;

    //Other public methods

};





