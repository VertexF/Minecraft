#ifndef WORLD_EVENT_HDR
#define WORLD_EVENT_HDR

namespace acid 
{
    class World;

    struct IWorldEvent
    {
        virtual ~IWorldEvent() = default;
        virtual void handle(World& world) = 0;
    };
}

#endif // !WORLD_EVENT_HDR
