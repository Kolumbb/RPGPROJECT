#include "TileMap.hpp"



//Initializers
auto TileMap::initTexturePacks(const std::filesystem::path& path) -> void {
    this->tileSheet = std::make_unique<sf::Texture>();
    this->tileSheet->loadFromFile(path.string());
}
auto TileMap::initCollisionBox() -> void {

}

//Constructors & Destructores
TileMap::TileMap(const float& gridSizeF, u_short width, u_short height)
    : gridSizeF(gridSizeF), gridSizeU(static_cast<unsigned>(gridSizeF)),
      layers(1), gameSize(sf::Vector2u(width, height)),
    gameSizeInPixels(sf::Vector2u (width * this->gridSizeU, height * this->gridSizeU)){



    this->tileMap.resize(this->gameSize.x, std::vector<std::vector<std::shared_ptr<Tile>>>());
    for(auto x = 0 ; x < this->gameSize.x ; x++){
        for(auto y = 0 ; y < this->gameSize.y ; y++) {
            this->tileMap[x].resize(this->gameSize.y, std::vector<std::shared_ptr<Tile>>());
            for (auto z = 0; z < this->layers; z++) {
                this->tileMap[x][y].resize(this->layers, nullptr);
            }
        }
    }


    this->initTexturePacks();
    this->initCollisionBox();
}

//Update methods
auto TileMap::update(const float& dt, std::shared_ptr<Player> hero, std::shared_ptr<Slime> slime) -> void {
  this->updateWorldBoundsCollisions(hero);
  this->updateWorldBoundsCollisions(slime);

  this->updateCulling(hero, slime);
  this->updateTileCollisions(dt, hero);
  this->updateTileCollisions(dt, slime);
}

auto TileMap::updateWorldBoundsCollisions(std::shared_ptr<Entity> entity) -> void {
  //Game map bounds
  if (entity->getPositionF().x < 0.f){
    entity->setPosition(0.f, entity->getPositionF().y);
    entity->stopVelocityX();
  }
  else if (entity->getPositionF().x + entity->getGlobalBounds().width > this->gameSizeInPixels.x){
    entity->setPosition(this->gameSizeInPixels.x - entity->getGlobalBounds().width, entity->getPositionF().y);
    entity->stopVelocityX();
  }
  if (entity->getPositionF().y < 0.f){
    entity->setPosition(entity->getPositionF().x, 0.f);
    entity->stopVelocityY();
  }
  else if (entity->getPositionF().y + entity->getGlobalBounds().height > this->gameSizeInPixels.y){
    entity->setPosition(entity->getPositionF().x, this->gameSizeInPixels.y - entity->getGlobalBounds().height);
    entity->stopVelocityY();
  }
}

auto TileMap::updateCulling(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> entity2) -> void {

    this->playerCulling.fromX = entity->getGridPosition(this->gridSizeU).x - 1;
    if (this->playerCulling.fromX < 0)
      this->playerCulling.fromX = 0;
    else if (this->playerCulling.fromX > this->gameSizeInPixels.x)
      this->playerCulling.fromX = this->gameSizeInPixels.x;

    this->slimeCulling.fromX = entity2->getGridPosition(this->gridSizeU).x - 1;
    if (this->slimeCulling.fromX < 0)
      this->slimeCulling.fromX = 0;
    else if (this->slimeCulling.fromX > this->gameSizeInPixels.x)
      this->slimeCulling.fromX = this->gameSizeInPixels.x;

    this->playerCulling.toX = entity->getGridPosition(this->gridSizeU).x + 3;
    if (this->playerCulling.toX < 0)
      this->playerCulling.toX = 0;
    else if (this->playerCulling.toX > this->gameSizeInPixels.x)
      this->playerCulling.toX = this->gameSizeInPixels.x;

    this->slimeCulling.toX = entity2->getGridPosition(this->gridSizeU).x + 2;
    if (this->slimeCulling.toX < 0)
      this->slimeCulling.toX = 0;
    else if (this->slimeCulling.toX > this->gameSizeInPixels.x)
      this->slimeCulling.toX = this->gameSizeInPixels.x;

    this->playerCulling.fromY = entity->getGridPosition(this->gridSizeU).y - 1;
    if (this->playerCulling.fromY < 0)
      this->playerCulling.fromY = 0;
    else if (this->playerCulling.fromY > this->gameSizeInPixels.y)
      this->playerCulling.fromY = this->gameSizeInPixels.y;

    this->slimeCulling.fromY = entity2->getGridPosition(this->gridSizeU).y -1;
    if (this->slimeCulling.fromY < 0)
      this->slimeCulling.fromY = 0;
    else if (this->slimeCulling.fromY > this->gameSizeInPixels.y)
      this->slimeCulling.fromY = this->gameSizeInPixels.y;

    this->playerCulling.toY = entity->getGridPosition(this->gridSizeU).y + 2;
    if (this->playerCulling.toY < 0)
      this->playerCulling.toY = 0;
    else if (this->playerCulling.toY > this->gameSizeInPixels.y)
      this->playerCulling.toY = this->gameSizeInPixels.y;

    this->slimeCulling.toY = entity2->getGridPosition(this->gridSizeU).y + 1;
    if (this->slimeCulling.toY < 0)
      this->slimeCulling.toY = 0;
    else if (this->slimeCulling.toY > this->gameSizeInPixels.y)
      this->slimeCulling.toY = this->gameSizeInPixels.y;

  }



auto TileMap::updateTileCollisions(const float& dt, std::shared_ptr<Entity> entity) -> void {
  for (int x = this->playerCulling.fromX; x < this->playerCulling.toX; x++) {
    for (int y = this->playerCulling.fromY; y < this->playerCulling.toY; y++) {
      if (this->tileMap[x][y][this->playerCulling.layer] != nullptr) {
        auto playerBounds = entity->getGlobalBounds();
        sf::FloatRect wallBounds = this->tileMap[x][y][this->playerCulling.layer]->getGlobalBounds();
        sf::FloatRect nextPositionBounds = entity->getNextPosition(dt);

        if (this->tileMap[x][y][this->playerCulling.layer]->getCollision() &&
            this->tileMap[x][y][this->playerCulling.layer]->intersects(
                nextPositionBounds)) {
          //Bottom collision
          if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height){
            if(!entity->getJump()) entity->stopVelocityY();
          }
          //Top collision
          else {
            if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height) {
              if(!entity->getJump()) entity->stopVelocityY();
            }
            // Right collision
            if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width)
              entity->stopVelocityX();

            // Left collision
            else if (playerBounds.left > wallBounds.left &&
                     playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                     playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top) {
              entity->stopVelocityX();
              entity->setPosition(entity->getPositionF().x,entity->getPositionF().y);
            }
          }
        }
      }
    }
  }

  for (int x = this->slimeCulling.fromX; x < this->slimeCulling.toX; x++) {
    for (int y = this->slimeCulling.fromY; y < this->slimeCulling.toY; y++) {
      if (this->tileMap[x][y][this->slimeCulling.layer] != nullptr) {
        auto playerBounds = entity->getGlobalBounds();
        sf::FloatRect wallBounds = this->tileMap[x][y][this->slimeCulling.layer]->getGlobalBounds();
        sf::FloatRect nextPositionBounds = entity->getNextPosition(dt);

        if (this->tileMap[x][y][this->slimeCulling.layer]->getCollision() &&
            this->tileMap[x][y][this->slimeCulling.layer]->intersects(
                nextPositionBounds)) {
          //Bottom collision
          if (playerBounds.top < wallBounds.top)
          {
            if(!entity->getJump()){
              entity->stopVelocityY();
            }
          }
          //Top collision
          else {
            if (
                playerBounds.top > wallBounds.top &&
                playerBounds.top + playerBounds.height >
                    wallBounds.top + wallBounds.height) {
              if(!entity->getJump()){
                entity->stopVelocityY();
              }
            }
            // Right collision
            if (playerBounds.left < wallBounds.left &&
                playerBounds.left + playerBounds.width <
                    wallBounds.left + wallBounds.width) {
              entity->stopVelocityX();
            }
            // Left collision
            else if (playerBounds.left > wallBounds.left &&
                     playerBounds.left + playerBounds.width >
                         wallBounds.left + wallBounds.width &&
                     playerBounds.top < wallBounds.top + wallBounds.height &&
                     playerBounds.top + playerBounds.height > wallBounds.top) {
              entity->stopVelocityX();
            }
          }
        }
      }
    }
  }
}


//Render methods
auto TileMap::render(sf::RenderTarget* target, std::shared_ptr<Entity> entity) -> void {
    for (int x = 0; x < this->gameSize.x; x++)
      for (int y = 0; y < this->gameSize.y; y++)
        for (int z = 0; z < this->layers; z++) {
          if (tileMap[x][y][z] != nullptr) {
            tileMap[x][y][z]->render(target);
          }
        }
  }
  //}



















//Other public methods
auto TileMap::addTile(
    const u_short& x, const u_short& y, const u_short& z, const sf::IntRect& intRect,
    const bool& collision, const u_short& type
    ) -> void {

    if(x >= 0 && x < this->gameSize.x && y >= 0 && y < this->gameSize.y && z >=0 && z < this->layers){
        if(this->tileMap[x][y][z] == nullptr) {
            this->tileMap[x][y][z] = std::make_shared<Tile>(
                    x, y, this->gridSizeU, *tileSheet, intRect, collision, type
                    );
        }
    }
}

auto TileMap::removeTile(const u_short& x, const u_short& y, const u_short& z) -> void {
  if(x >= 0 && x < this->gameSize.x && y >= 0 && y < this->gameSize.y && z >=0 && z < this->layers){
        if(this->tileMap[x][y][z] != nullptr) {
            this->tileMap[x][y][z].reset();
        }
    }
}

auto TileMap::getTexture() const -> const std::shared_ptr<sf::Texture> {
    return this->tileSheet;
}

void TileMap::saveMapToFile(const std::filesystem::path &path) {
    /*
     * Format:
     * size x y
     * gridSize
     * layers
     * Tile
     * gridPos x y
     * layer
     * textureRect x y
     * collision
     * type
     */

    auto ofs = std::ofstream(path);
    if(ofs.good()) std::cout << "File found\n";
    if (ofs) {
        ofs << this->gameSize.x << " " << this->gameSize.y << "\n"
            << this->gridSizeU << "\n"
            << this->layers << "\n";

            for(auto x = 0 ; x < this->tileMap.size() ; x++)
                for (auto y = 0; y < this->tileMap[x].size(); y++)
                    for (auto z = 0; z < this->tileMap[x][y].size(); z++)
                        if(this->tileMap[x][y][z]) ofs << x <<" " <<  y << " " << z << " " << this->tileMap[x][y][z]->getTile() << " ";

    }else std::cout << "PLEASE CHECK GAME MAP LOCATION - THERE IS NO FILE" << std::endl;
    ofs.close();
}

void TileMap::loadMapFromFile(const std::filesystem::path &path) {
/*
     * Format:
     * size x y
     * gridSize
     * layers
     * gridPos x y
     * textureRect x y
     * collision
     * type
     */

    //Remove all map elements and the map itself before loading from file
    this->tileMap.clear();
    this->initTexturePacks();

    auto ifs = std::ifstream(path);
    if(ifs.good()) std::cout << "File found\n";
    if (ifs) {
        auto size = sf::Vector2u();
        auto gridSizeU = u_short();
        auto layers = u_short();
        auto x = u_short();
        auto y = u_short();
        auto z = u_short ();
        auto textureRectX = u_short();
        auto textureRectY = u_short();
        auto collision = bool();
        auto type = u_short();
        auto texture = this->tileSheet;

        ifs >> size.x >> size.y >> gridSizeU >> layers;

        this->gridSizeF = static_cast<float>(gridSizeU);
        this->gridSizeU = gridSizeU;
        this->layers = layers;
        this->gameSize = size;
        this->initTexturePacks();

        this->tileMap.resize(this->gameSize.x, std::vector<std::vector<std::shared_ptr<Tile>>>());
        for(auto x = 0 ; x < this->gameSize.x ; x++){
            for(auto y = 0 ; y < this->gameSize.y ; y++) {
                this->tileMap[x].resize(this->gameSize.y, std::vector<std::shared_ptr<Tile>>());
                for (auto z = 0; z < this->layers; z++) {
                    this->tileMap[x][y].resize(this->layers, nullptr);
                }
            }
        }
        while(ifs >> x >> y >> z >> textureRectX >> textureRectY >> collision >> type){
            this->tileMap[x][y][z] = std::make_shared<Tile>(
                    x, y, this->gridSizeF, *this->tileSheet,
                    sf::IntRect(
                            textureRectX,textureRectY,
                            this->gridSizeU,this->gridSizeU
                            ),
                    collision, type
                    );
        }





    }else{
        std::cout << "PLEASE CHECK GAME MAP LOCATION - THERE IS NO FILE" << std::endl;
    }
    ifs.close();
}

//Accessors & Modifiers

