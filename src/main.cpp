#include "Game.hpp"



auto main() -> int {
   auto game = std::make_unique<Game>();
   game->run();
}
