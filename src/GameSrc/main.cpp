#include <iostream>

#include <memory>
#include "../Acid/Source/Application.h"

int main() 
{
    std::unique_ptr<acid::Application> application = std::make_unique<acid::Application>("Minecraft");
    application->mainLoop();

    return 0;
}