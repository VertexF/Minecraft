#ifndef PLAYING_STATE_HDR
#define PLAYING_STATE_HDR

#include "StateBase.h"

namespace acid 
{
    class StatePlaying : public StateBase 
    {
    public:
        StatePlaying(Application& app);
        virtual ~StatePlaying() noexcept = default;

        virtual void handleEvent(sf::Event e);
        virtual void handleInput();

        virtual void update(float deltaTime);
        virtual void render(RenderMaster& renderer);
    };
}

#endif // !PLAYING_STATE_HDR
