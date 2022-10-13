#ifndef WORLD_HDR
#define WORLD_HDR

#include <vector>
#include <set>
#include <memory>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <atomic>

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
    class Player;

    class World
    {
    public:
        World(const Camera& camera, Player& player);
        ~World();

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

        void setSpwanPoint();

        std::vector<std::unique_ptr<IWorldEvent>> _events;
        std::unordered_map<sf::Vector3i, ChunkSection*, hash<sf::Vector3i>> _chunkUpdates;
        ChunkManager _chunkManager;

        std::atomic<bool> _isRunning{true};
        std::vector<std::thread> _chunkLoadThreads;
        std::mutex _mutex;
        std::mutex _genMutex;

        glm::vec3 _playerSpawnPoint;

        int _loadDistance;
    };
}

#endif // !WORLD_HDR
