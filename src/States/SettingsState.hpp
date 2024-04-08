#pragma once
#include "../ResourcePath.hpp"
#include "../Gui/DisplaySettingsMenu.hpp"
#include "State.hpp"
class SettingsState :
    public State{

private:
    //Variables & Resources
    bool paused;
    std::unique_ptr <sf::RectangleShape> background;
    std::map<std::string, std::unique_ptr<gui::Button>> buttons;
    std::unique_ptr <DisplaySettingsMenu> dMenu;

    //Private functions

    //Initializers
    auto initBackground(const std::filesystem::path& path = "../Resources/mainMenu/background.png" ) -> void;
    auto initKeyBinds(const std::filesystem::path& path = "../Resources/config/key_binds.settingsState.ini") -> void;
    auto initButtons(u_short offset = 0) -> void;
    auto initDisplaySettingsMenu() -> void;
    auto initButtonNames() -> void;

    //Update methods
    auto update(const float& dt) -> void;
    auto updateDisplaySettings(const float& dt) -> void;
    auto updateSettingsState(const float& dt) -> void;


    auto updateButtons(const float& dt) -> void;
    auto updateKeyBindsInput(const float& dt) -> void;

    //Render methods
    auto render(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderPaused(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderUnPaused(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderButtons(std::shared_ptr<sf::RenderTarget> target) -> void;


public:

    explicit SettingsState(StateData& state_data);
    ~SettingsState() = default;
};

