#include "../ResourcePath.hpp"


class HitBoxComponent {
private:
  // Resources & Variables
  sf::Sprite &sprite;
  sf::RectangleShape hitBox;
  sf::FloatRect nextPosition;
  float offsetX;
  float offsetY;

  // Initializers
  auto initHitBox(const float &width, const float &height) -> void;
  auto initNextPosition(const float &width, const float &height) -> void;

protected:
public:
  // Constructors & Destructors
  HitBoxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width,
                  float height);
  ~HitBoxComponent() = default;

  // Update methods
  auto update() -> void;

  // Render methods
  auto render(sf::RenderTarget *target) -> void;

  // Other public methods
  auto intersects(const sf::FloatRect &fRect) -> bool;

  // Accessors & Modifiers
  auto getPosition() const -> const sf::Vector2f&;
  auto setPosition(const float &posX, const float &posY) -> void;
  auto getGlobalBounds() const -> const sf::FloatRect&;
  auto getNextPosition(const sf::Vector2f &velocity) -> const sf::FloatRect &;
};
