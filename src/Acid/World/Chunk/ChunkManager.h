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
    class Camera;

    class ChunkManager 
    {
    public:
        ChunkManager(World& world);

        std::unordered_map<VectorXZ, Chunk, hash<VectorXZ>>& getChunks();
        Chunk& getChunk(int x, int z);
        Chunk& qGetChunk(int x, int z);

        bool makeMesh(int x, int z, const Camera& camera);

        bool chunkLoadedAt(int x, int z) const;
        bool chunkExistsAt(int x, int z) const;

        void loadChunk(int x, int z);
        void unloadChunk(int x, int z);
    private:
        std::unordered_map<VectorXZ, Chunk, hash<VectorXZ>> _chunks;
        World* _world;
    };
}

#endif // !CHUNK_MANAGER_HDR
