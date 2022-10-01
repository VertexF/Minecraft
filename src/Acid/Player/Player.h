#ifndef PLAYER_HDR
#define PLAYER_HDR

#include "../Source/Entity.h"

namespace acid 
{
    class Player : public Entity 
    {
    public:
        Player();

        void handleInput();

        void update(float dt);
    private:
        void keyboardInput();
        void mouseInput();
    };
}

#endif // !PLAYER_HDR
