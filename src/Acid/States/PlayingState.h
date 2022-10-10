#ifndef PLAYING_STATE_HDR
#define PLAYING_STATE_HDR

#include "StateBase.h"
#include "../Player/Player.h"
#include "../Util/FPSCounter.h"
#include "../World/World.h"

namespace acid 
{
    class StatePlaying : public StateBase 
    {
    public:
        StatePlaying(Application& app);
        virtual ~StatePlaying() = default;

        virtual void handleEvent(sf::Event e) override;
        virtual void handleInput() override;

        virtual void update(float deltaTime) override;
        virtual void render(RenderMaster& renderer) override;

        virtual void onOpen() override;
    private:
        Player _player;

        sf::RectangleShape _crossHair;
        sf::Texture _crossHairTexture;

        FPSCounter _fpsCounter;
        World _world;
    };
}

#endif // !PLAYING_STATE_HDR
