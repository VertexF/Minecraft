#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "../Util/Singleton.h"
#include "../Util/Random.h"
#include "../World/Block/BlockDatabase.h"

namespace acid
{

#define RANDOM_GENERATOR (Singleton<RandomSingleton>::getInstance())
#define BLOCK_DATABASE (Singleton<BlockDatabase>::getInstance())

}

#endif // !GLOBAL_HDR
