#include "World.h"

#include <algorithm>

#include "../Renderer/RenderMaster.h"
#include "../Source/Camera.h"
#include "Chunk/Chunk.h"
#include "../Player/Player.h"

namespace 
{
    constexpr int RENDER_DISTACE = 12;
    constexpr float GRAV = -3;
}

namespace acid
{
    World::World(const Camera& camera, Player& player) :
        _chunkManager(*this), _loadDistance(2)
    {
        for (int i = 0; i < 2; i++) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            _chunkLoadThreads.emplace_back([&]()
            {
                while (_isRunning)
                {
                    loadChunks(camera);
                }
            });
        }
    }

    World::~World() 
    {
        _isRunning = false;
        for (auto& thread : _chunkLoadThreads) 
        {
            thread.join();
        }
    }

    ChunkBlock World::getBlock(int x, int y, int z)
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        return _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).getBlock(blockPosition.x, y, blockPosition.z);
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).setBlock(blockPosition.x, y, blockPosition.z, block);
    }

    void World::update(const Camera& camera)
    {
        static ToggleKey key(sf::Keyboard::C);

        if (key.isKeyPressed()) 
        {
            _mutex.lock();
            _chunkManager.deleteMeshes();
            _loadDistance = 2;
            _mutex.unlock();
        }

        for (auto& event : _events)
        {
            event->handle(*this);
        }
        _events.clear();

        updateChunks();
    }

    void World::updateChunk(int blockX, int blockY, int blockZ)
    {
        _mutex.lock();
        auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, ChunkSection& section) 
        {
            _chunkUpdates.emplace(key, &section);
        };

        auto chunkPosition = getChunkXZ(blockX, blockZ);
        auto chunkY = blockY / CHUNK_SIZE;

        sf::Vector3i  key(chunkPosition.x, chunkY, chunkPosition.z);
        addChunkToUpdateBatch(key, _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).getSection(chunkY));

        auto sectionBlockXZ = getBlockXZ(blockX, blockZ);
        auto sectionBlockY = blockY % CHUNK_SIZE;

        if (sectionBlockXZ.x == 0) 
        {
            sf::Vector3i newKey(chunkPosition.x - 1, chunkY, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockXZ.x == CHUNK_SIZE - 1) 
        {
            sf::Vector3i newKey(chunkPosition.x + 1, chunkY, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }

        if (sectionBlockY == 0)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY - 1, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockY == CHUNK_SIZE - 1)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY + 1, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }

        if (sectionBlockXZ.z == 0)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY, chunkPosition.z - 1);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockXZ.z == CHUNK_SIZE - 1)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY, chunkPosition.z + 1);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        _mutex.unlock();
    }

    void World::renderWorld(RenderMaster& master, const Camera& camera)
    {
        _mutex.lock();
        master.drawSky();

        std::unordered_map<VectorXZ, Chunk, hash<VectorXZ>>& chunkMap = _chunkManager.getChunks();
        for(auto iterator = chunkMap.begin(); iterator != chunkMap.end();)
        {
            Chunk& chunk = iterator->second;

            int cameraX = camera.position.x;
            int cameraZ = camera.position.z;

            int minX = (cameraX / CHUNK_SIZE) - RENDER_DISTACE;
            int minZ = (cameraZ / CHUNK_SIZE) - RENDER_DISTACE;
            int maxX = (cameraX / CHUNK_SIZE) + RENDER_DISTACE;
            int maxZ = (cameraZ / CHUNK_SIZE) + RENDER_DISTACE;

            auto location = chunk.getLocation();

            if(minX > location.x || minZ > location.y ||
               maxX < location.x || maxZ < location.y)
            {
                iterator = chunkMap.erase(iterator);
                continue;
            }
            else 
            {
                chunk.drawChunks(master, camera);
                iterator++;
            }
        }
        _mutex.unlock();
    }

    ChunkManager& World::getChunkManager() 
    {
        return _chunkManager;
    }

    VectorXZ World::getBlockXZ(int x, int z) 
    {
        return
        {
            x % CHUNK_SIZE,
            z % CHUNK_SIZE
        };
    }

    VectorXZ World::getChunkXZ(int x, int z) 
    {
        return
        {
            x / CHUNK_SIZE,
            z / CHUNK_SIZE
        };
    }

    void World::collisionTest(Entity& entity) 
    {
    }

    void World::loadChunks(const Camera& camera) 
    {
        bool isMeshMade = false;
        int cameraX = camera.position.x / CHUNK_SIZE;
        int cameraZ = camera.position.z / CHUNK_SIZE;

        for (int i = 0; i < _loadDistance; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1))
                ;            int minX = std::max(cameraX - i, 0);
            int minZ = std::max(cameraZ - i, 0);
            int maxX = cameraX + i;
            int maxZ = cameraZ + i;

            for (int x = minX; x < maxX; x++)
            {
                for (int z = minZ; z < maxZ; z++)
                {
                    _mutex.lock();
                    isMeshMade = _chunkManager.makeMesh(x, z, camera);
                    _mutex.unlock();
                }

                //if (isMeshMade)
                //{
                //    break;
                //}
            }

            if (isMeshMade)
            {
                break;
            }
        }

        if (isMeshMade == false)
        {
            _loadDistance++;
        }
        if (_loadDistance >= RENDER_DISTACE)
        {
            _loadDistance = 2;
        }
    }

    void World::updateChunks() 
    {
        _mutex.lock();
        for (auto& newChunk : _chunkUpdates)
        {
            ChunkSection& section = *newChunk.second;
            section.makeMesh();
        }
        _chunkUpdates.clear();
        _mutex.unlock();
    }

    void World::setSpwanPoint() 
    {
        sf::Clock timer;

        //auto h = _chunkManager.get
    }
}