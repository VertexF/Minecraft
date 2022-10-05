#ifndef CHUNK_MANAGER_HDR
#define CHUNK_MANAGER_HDR

#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "../../Maths/Vector2XZ.h"
#include "Chunk.h"

namespace acid 
{
    class World;

    class ChunkManager 
    {
    public:
        ChunkManager(World& world);

        Chunk& getChunk(int x, int z);

        const std::unordered_map<VectorXZ, Chunk>& getChunks() const;

        bool makeMesh(int x, int z);

        void queueChunk(int x, int z);

        void update();
    private:
        std::unordered_map<VectorXZ, Chunk> _chunks;
        World* _world;
    };
}

#endif // !CHUNK_MANAGER_HDR
