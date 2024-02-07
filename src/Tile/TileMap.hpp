#pragma once

#include "../ResourcePath.hpp"
#include "../Tile/Tile.hpp"
#include "../StateData.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Slime.hpp"

class TileMap {
private:
    //Variables & Resources
    u_short layers;
    float gridSizeF;
    u_short gridSizeU;
    sf::Vector2u gameSize;
    sf::Vector2u gameSizeInPixels;
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> tileMap;
    std::shared_ptr<sf::Texture> tileSheet;
    my::Culling playerCulling;
    my::Culling slimeCulling;

    //Methods

    //Initializers
    auto initTexturePacks(const std::filesystem::path& path = "../Resources/editorState/Tileset1.png") -> void;
    auto initCollisionBox() -> void;
protected:
public:
    //Constructors & Destructors
    TileMap(const float& gridSizeF, u_short width, u_short height);
    ~TileMap() = default;

    //Update methods
    auto update(const float& dt, std::shared_ptr<Player> hero = nullptr, std::shared_ptr<Slime> slime = nullptr) -> void;
    auto updateWorldBoundsCollisions(std::shared_ptr<Entity> entity = nullptr) -> void;
    auto updateCulling(std::shared_ptr<Entity> entity1 = nullptr, std::shared_ptr<Entity> entity2 = nullptr) -> void;
    auto updateTileCollisions(const float& dt, std::shared_ptr<Entity> entity = nullptr) -> void;

    //Render methods
    auto render(sf::RenderTarget* target, std::shared_ptr<Entity> entity = nullptr) -> void;

    //Other public methods
    auto addTile(
            const u_short& x, const u_short& y, const u_short& z, const sf::IntRect& intRect,
            const bool& collision, const u_short& type) -> void;
    auto removeTile(const u_short& x, const u_short& y, const u_short& z) -> void;
    auto getTexture() const -> const std::shared_ptr<sf::Texture>;

    auto saveMapToFile(const std::filesystem::path& path = "../Resources/config/SaveData/save_01.sv") -> void;
    auto loadMapFromFile(const std::filesystem::path& path = "../Resources/Config/SaveData/save_01.sv") -> void;

    auto getCollisionBox() const -> const sf::FloatRect&;


};


