#pragma once

#include "../ResourcePath.hpp"
#include "../StateData.hpp"

namespace gui {
    enum ButtonState {
        IDLE = 0, HOVER, PRESSED
    };

    class Button {
    private:
        //Variables & Resources
        sf::Text text;
        ButtonState btnState;
        sf::RectangleShape shape;
        sf::Vector2f size;
        sf::Vector2f position;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

        //Initializers
        auto initShape(float posX, float posY, float width, float height) -> void;

        auto initText(std::string text, u_short characterSize, const sf::Font &font) -> void;

        //Private Accessors

        auto updateBtnState() -> void;

        auto updateMousePosition(const float &dt, const sf::Vector2f &mousePositionn) -> void;


    protected:

    public:
        //Public Accessors
        auto isPressed() const -> bool const;

        auto getText() const -> std::string const;

        //Modifiers
        auto setText(const std::string &text) -> void;

        //Constructors & Destructors
        Button(float posX, float posY, float width, float height,
               std::string text, u_short characterSize, sf::Color textIdleColor,
               sf::Color textHoverColor, sf::Color textActiveColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
               const sf::Font &font, sf::Color outlineIdleColor = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outlineActiveColor = sf::Color::Transparent
        );

        ~Button() = default;

        //Methods
        auto update(const float &dt, const sf::Vector2f &mousePosition) -> void;

        auto render(sf::RenderTarget* target) const -> void const;

    };

    //Drop Down List Class
    class DropDownList {
    private:
        //Resources & Variables
        std::vector<std::shared_ptr<gui::Button >> dropDownList;
        std::shared_ptr<gui::Button> activeElement;
        std::vector<std::string> str;
        StateData &stateData;
        bool shownList;
        std::string name;
        my::Timer timer;

        //Initializers
        auto initDropDownList(u_short offsetB = 3) -> void;


    public:
        //Constructors & Destructors
        DropDownList(
                const std::string &name, u_short buttonWidth,
                StateData &stateData, std::vector<std::string> str,
                bool shown = false
        );

        ~DropDownList() = default;

        //Update methods
        auto update(const float &dt, const sf::Vector2f &mousePosition) -> void;

        //Render methods
        auto render(sf::RenderTarget* target) const -> void const;

        //Getters
        auto getResolution() const -> const sf::VideoMode;

        auto getFullScreen() const -> const bool;

        auto getFrameRate() const -> const u_short;

        auto getVSync() const -> const bool;

        auto getShown() const -> const bool;

        auto setShown() -> void;

        auto getText() const -> const std::string;
    };

    class TextureSelector {
    private:
        //Variables && Resources
        bool active;

        u_short gridSizeU;
        sf::Vector2u mousePosGrid;
        sf::Vector2f position;
        my::Timer timer;
        sf::IntRect internalRect;
        sf::RectangleShape bounds;
        sf::RectangleShape selector;
        sf::Sprite sheet;

        //Initializers
        auto initBounds(const float &posX, const float &posY, const float &width, const float &height) -> void;

        auto initSpriteSheet(const float &posX, const float &posY, const sf::Texture &textureSheet) -> void;

        auto initSelector(const float &posX, const float &posY) -> void;

    protected:
    public:
        //Constructors & Destructors
        TextureSelector(
                const float &posX, const float &posY, const float &width, const float &height,
                const u_short &gridSizeU, const sf::Texture &textureSheet, StateData &stateData
        );

        ~TextureSelector() = default;

        //Update methods
        auto update(const sf::Vector2u& selectorPosition) -> void;

        //Render methods
        auto render(sf::RenderTarget* target) -> void;

        auto renderActive(sf::RenderTarget* target, const sf::View& defaultView, const sf::View& view) -> void;

        //Other Public methods
        auto getActive() const -> const bool;
        auto setActive(const bool& yn) -> void;
        auto getPosition() const -> const sf::Vector2f&;
        auto getBounds(const sf::Vector2f& mousePosWindow) const -> const bool;
        auto getInternalRect() const -> const sf::IntRect &;

    };


}
