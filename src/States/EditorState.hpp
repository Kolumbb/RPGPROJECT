#pragma once
#include "../ResourcePath.hpp"
#include "State.hpp"
#include "../Gui/PauseMenu.hpp"
#include "../Tile/TileMap.hpp"

class EditorState :
    public State{

private:
    //Variables & Resources
    bool paused;
    bool collision;
    u_short layer;
    sf::Text mouseText;
    sf::RectangleShape selector;
    sf::View gameView;
    float cameraSpeed;
    std::unique_ptr <PauseMenu> pMenu;
    std::unique_ptr <TileMap> tileMap;
    std::unique_ptr<sf::RectangleShape> sideBar;
    std::unique_ptr<gui::TextureSelector> textureSelector;
    std::unique_ptr<gui::Button> texturePack;
    bool texturePackActive;

    // std::map<std::string, gui::Button*> buttons;
    //Private functions

    //Initializers
    auto initBackground(const std::filesystem::path& path = "../Resources/mainMenu/background.png") -> void;
    auto initKeyBinds(const std::filesystem::path& path = "../Resources/config/key_binds_editorstate.ini") -> void;
    auto initPausedMenu() -> void;
    auto initTileMap() -> void;
    auto initGui() -> void;
    auto initMouseText() -> void;
    auto initView() -> void;



    //Update methods
    auto update(const float& dt) -> void;
    auto updateButtons(const float& dt) -> void;
    auto updatePaused(const float& dt) -> void;
    auto updateUnPaused(const float& dt) -> void;
    auto updateKeyBindsInput(const float& dt) -> void;
    auto updateGui() -> void;
    auto updateEditorInput(const float& dt) -> void;



    //Render methods
    auto render(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderPaused(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderUnPaused(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderGui(std::shared_ptr<sf::RenderTarget> target) -> void;



public:
    //Constructors & Destructors
    EditorState(StateData& state_data, bool collision = false, u_short type = TileType::DEFAULT);
    ~EditorState() = default;


};



