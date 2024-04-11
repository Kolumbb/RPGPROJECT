#pragma once

#include "../ResourcePath.hpp"
#include "../Tile/Tile.hpp"
#include "../StateData.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Slime.hpp"

class TileMap {
private:
    //Variables & Resources
    my::Timer timer;
    u_short layers;
    float gridSizeF;
    u_short gridSizeU;
    bool colision;
    sf::Vector2u gameSize;
    sf::Vector2u gameSizeInPixels;
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> tileMap;
    std::shared_ptr<sf::Texture> tileSheet;
    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities;

    //Initializers
    auto initTexturePacks(const std::filesystem::path& path) -> void;
    //Private update Methods
    auto updateWorldBoundsCollisions(std::shared_ptr<Entity>& entity) -> void;
    auto updateCulling(std::shared_ptr<Entity>& entity) -> void;
    auto updateTileCollisions(const float& dt, const std::shared_ptr<Entity>& entity) -> void;
public:
    //Constructors & Destructors
    TileMap(const float& gridSizeF, u_short width, u_short height);
    ~TileMap() = default;

    //Update methods
    auto update(const float& dt, std::vector<std::shared_ptr<Entity>>& mapOfEntities) -> void;
    auto checkEntitiesCollisions(std::vector<std::shared_ptr<Entity>>& mapOfEntities, const float& dt) -> void;

    //Render methods
    auto render(std::shared_ptr<sf::RenderTarget> target) -> void;
    auto renderCollisionBox(std::shared_ptr<sf::RenderTarget> target) const -> void;

    //Other public methods
    auto addTile(const u_short& x, const u_short& y, const u_short& z, const sf::IntRect& intRect, const bool& collision, const u_short& type) -> void;
    auto removeTile(const u_short& x, const u_short& y, const u_short& z) -> void;
    auto getTexture() const -> const std::shared_ptr<sf::Texture>;

    auto saveMapToFile(const std::filesystem::path& path = "../Resources/config/SaveData/save_01.sv") -> void;
    auto loadMapFromFile(const std::filesystem::path& path = "../Resources/Config/SaveData/save_01.sv") -> void;

};


