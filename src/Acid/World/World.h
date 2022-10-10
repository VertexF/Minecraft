#ifndef WORLD_HDR
#define WORLD_HDR

#include <vector>
#include <set>
#include <memory>
#include <unordered_map>

#include "../Maths/Vector2XZ.h"
#include "Chunk/ChunkBase.h"
#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"
#include "Event/IWorldEvent.h"
#include "Event/PlayerDigEvent.h"

namespace acid 
{
    class RenderMaster;
    class Camera;
    struct Entity;

    class World
    {
    public:
        World(const Camera& camera);
        ~World() = default;

        ChunkBlock getBlock(int x, int y, int z);
        void setBlock(int x, int y, int z, const ChunkBlock& block);

        void update(const Camera& camera);
        void updateChunk(int blockX, int blockY, int blockZ);

        void renderWorld(RenderMaster& master, const Camera& camera);
        ChunkManager& getChunkManager();

        static VectorXZ getBlockXZ(int x, int z);
        static VectorXZ getChunkXZ(int x, int z);

        void collisionTest(Entity& entity);

        template<typename T, typename... Args>
        void addEvent(Args&&... args) 
        {
            _events.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

    private:
        void loadChunks(const Camera& camera);
        void updateChunks();

        std::vector<std::unique_ptr<IWorldEvent>> _events;
        std::unordered_map<sf::Vector3i, ChunkSection*, hash<sf::Vector3i>> _chunkUpdates;
        ChunkManager _chunkManager;

        int _loadDistance;
    };
}

#endif // !WORLD_HDR
