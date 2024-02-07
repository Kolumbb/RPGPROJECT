#pragma once
#include "../ResourcePath.hpp"
#include "State.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"
#include "EditorState.hpp"


class MainMenuState :
    public State{

private:
    //Variables & Resources
    sf::RectangleShape shape;
    std::map<std::string, std::unique_ptr<gui::Button>> buttons;
    //Private functions

    //Initializers
    auto initBackground(const std::filesystem::path& path = "../Resources/mainMenu/background.png") -> void;
    auto initKeyBinds(const std::filesystem::path& path = "../Resources/config/key_binds_mainmenustate.ini") -> void;
    auto initButtons(const sf::Font& font, u_short offsetB = 6) -> void;
    auto initButtonNames() -> void;


    //Update methods
    
    auto update(const float& dt) -> void override;
    auto updateButtons(const float& dt) -> void;

    //Render methods
    auto render(sf::RenderTarget* target) -> void;
    auto renderButtons(sf::RenderTarget* target) -> void;

protected:

public:
    //Constructors & Destructors
    explicit MainMenuState(StateData& stateData);
    ~MainMenuState() = default;
    
    auto resolutionChanged() -> void;
};

