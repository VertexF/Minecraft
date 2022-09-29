#ifndef GAME_HDR
#define GAME_HDR

#include <memory>
#include "Application.h"

namespace game
{
    class Game
    {
    public:
        Game();

        void mainLoop();
    private:
        std::unique_ptr<acid::Application> _application;
    };
}

#endif // !GAME_HDR
