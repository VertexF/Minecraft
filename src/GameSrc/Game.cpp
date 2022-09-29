#include "Game.h"

namespace game
{
    Game::Game() :
        _application(std::make_unique<acid::Application>())
    {
    }

    void Game::mainLoop()
    {
    }
}