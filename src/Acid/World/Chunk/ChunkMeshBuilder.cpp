#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"
#include "../Block/BlockID.h"
#include "../Block/BlockData.h"
#include "../../Source/Global.h"

namespace 
{
    const std::vector<GLfloat> frontFace
    {
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f,
        1.f, 1.f, 1.f,
        0.f, 1.f, 1.f
    };

    const std::vector<GLfloat> backFace
    {
        1.f, 0.f, 0.f,
        0.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f
    };

    const std::vector<GLfloat> leftFace
    {
        0.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        0.f, 1.f, 1.f,
        0.f, 1.f, 0.f
    };

    const std::vector<GLfloat> rightFace
    {
        1.f, 0.f, 1.f,
        1.f, 0.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, 1.f, 1.f
    };

    const std::vector<GLfloat> topFace
    {
        0.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 0.f
    };

    const std::vector<GLfloat> bottomFace
    {
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        1.f, 0.f, 1.f,
        0.f, 0.f, 1.f
    };

    const std::vector<GLfloat> xFace1
    {
        0, 0, 0,
        1, 0, 1,
        1, 1, 1,
        0, 1, 0,
    };

    const std::vector<GLfloat> xFace2
    {
        0, 0, 1,
        1, 0, 0,
        1, 1, 0,
        0, 1, 1,
    };

    struct AdjacentBlockDirections 
    {
        sf::Vector3i up;
        sf::Vector3i down;
        sf::Vector3i left;
        sf::Vector3i right;
        sf::Vector3i front;
        sf::Vector3i back;

        void update(int x, int y, int z) 
        {
            up =    { x,     y + 1, z     };
            down =  { x,     y - 1, z     };
            left =  { x - 1, y,     z     };
            right = { x + 1, y,     z     };
            front = { x,     y,     z + 1 };
            back =  { x,     y,     z - 1 };
        }
    };

    constexpr GLfloat LIGHT_TOP = 1.f;
    constexpr GLfloat LIGHT_X = 0.8f;
    constexpr GLfloat LIGHT_Z = 0.6f;
    constexpr GLfloat LIGHT_BOT = 0.4f;
}

namespace acid 
{
    ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunkSection, ChunkMeshCollection& chunkMeshes) :
        _chunkSection(&chunkSection), _chunkMeshes(&chunkMeshes)
    {
    }

    void ChunkMeshBuilder::buildMesh() 
    {
        AdjacentBlockDirections direction;

        for (int8_t y = 0; y < CHUNK_SIZE; ++y) 
        {
            if (shouldMakeLayer(y) == false)
            {
                continue;
            }

            for (int8_t x = 0; x < CHUNK_SIZE; ++x)
            {
                for (int8_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    sf::Vector3i position(x, y, z);
                    ChunkBlock block = _chunkSection->getBlock(x, y, z);
                    setActiveMesh(block);

                    if (block == BlockID::AIR)
                    {
                        continue;
                    }

                    _blockData = &block.getData();
                    auto& data = *_blockData;

                    if (data.meshType == BlockMeshType::X) 
                    {
                        addXBlockToMesh(data.texTopCoord, position);
                        continue;
                    }

                    direction.update(x, y, z);

                    tryAddFaceToMesh(topFace, data.texTopCoord, position, direction.up, LIGHT_TOP);
                    tryAddFaceToMesh(bottomFace, data.texBottomCoord, position, direction.down, LIGHT_BOT);
                    tryAddFaceToMesh(leftFace, data.texSideCoord, position, direction.left, LIGHT_X);
                    tryAddFaceToMesh(rightFace, data.texSideCoord, position, direction.right, LIGHT_X);
                    tryAddFaceToMesh(frontFace, data.texSideCoord, position, direction.front, LIGHT_Z);
                    tryAddFaceToMesh(backFace, data.texSideCoord, position, direction.back, LIGHT_Z);
                }
            }
        }
    }

    void ChunkMeshBuilder::setActiveMesh(ChunkBlock block)
    {
        if(block.id == static_cast<int>(BlockID::WATER)) 
        {
            _activeMesh = &_chunkMeshes->waterMesh;
        }
        else 
        {
            _activeMesh = &_chunkMeshes->solidMesh;
        }
    }

    void ChunkMeshBuilder::addXBlockToMesh(const sf::Vector2i& textureCoords,
                                           const sf::Vector3i& blockPosition) 
    {
        auto texCoords = BLOCK_DATABASE.textureAtlas.getTexture(textureCoords);

        _activeMesh->addFace(xFace1, texCoords, _chunkSection->getLocation(), blockPosition, LIGHT_X, true);
        _activeMesh->addFace(xFace2, texCoords, _chunkSection->getLocation(), blockPosition, LIGHT_X, true);
    }

    void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                                            const sf::Vector2i& textureCoords,
                                            const sf::Vector3i& blockPosition,
                                            const sf::Vector3i& blockFacing,
                                            GLfloat cardinalLight) 
    {
        if (shouldMakeFace(blockFacing, *_blockData))
        {
            auto texCoords = BLOCK_DATABASE.textureAtlas.getTexture(textureCoords);

            _activeMesh->addFace(blockFace, texCoords, _chunkSection->getLocation(), blockPosition, cardinalLight, false);
        }
    }

    bool ChunkMeshBuilder::shouldMakeFace(const sf::Vector3i& adjBlock, const BlockDataHolder& blockData)
    {
        auto block = _chunkSection->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);

        auto& data = block.getData();
        if (block == BlockID::AIR)
        {
            return true;
        }
        else if((data.isOpaque == false) && (data.id != _blockData->id))
        {
            return true;
        }

        return false;
    }

    bool ChunkMeshBuilder::shouldMakeLayer(int layer)
    {
        auto adjIsSolid = [&](int dx, int dz)
        {
            const ChunkSection& sect = _chunkSection->getAdjacent(dx, dz);
            return sect.getLayer(layer).isAllSolid();
        };

        return ((_chunkSection->getLayer(layer).isAllSolid() == false) ||
            (_chunkSection->getLayer(layer + 1).isAllSolid() == false) ||
            (_chunkSection->getLayer(layer - 1).isAllSolid() == false) ||
            (adjIsSolid(1, 0) == false) ||
            (adjIsSolid(0, 1) == false) ||
            (adjIsSolid(-1, 0) == false) ||
            (adjIsSolid(0, -1) == false));
    }
}