#include <iostream>

#include "Game.h"

int main() 
{
    game::Game game;
    game.mainLoop();

    std::cout << "Hello world." << std::endl;
    return 0;
}