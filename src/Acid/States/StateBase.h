#ifndef STATE_BASE_HDR
#define STATE_BASE_HDR

#include <SFML/Graphics.hpp>

namespace acid 
{
    class RenderMaster;
    class Application;

    class StateBase 
    {
    public:
        StateBase(Application& app) :
            _application(&app) 
        {
        }
        virtual ~StateBase() noexcept = default;

        virtual void handleEvent(sf::Event e) = 0;
        virtual void handleInput() = 0;

        virtual void update(float deltaTime) = 0;
        virtual void render(RenderMaster& renderer) = 0;

        virtual void onOpen() = 0;
    protected:
        Application* _application;
    };
}

#endif // !STATE_BASE_HDR
