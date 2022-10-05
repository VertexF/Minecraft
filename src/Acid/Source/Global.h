#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "../Util/Singleton.h"
#include "../Util/Random.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/World.h"
#include "../World/Chunk/ChunkMesh.h"

namespace acid
{

#define RANDOM_GENERATOR (Singleton<RandomSingleton>::getInstance())
#define BLOCK_DATABASE (Singleton<BlockDatabase>::getInstance())
#define WORLD (Singleton<World>::getInstance())
#define CHUNK_MESH (Singleton<ChunkMesh>::getInstance())

}

#endif // !GLOBAL_HDR
