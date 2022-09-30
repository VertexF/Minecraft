#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "../Util/Singleton.h"
#include "../Util/Random.h"

namespace acid
{

#define RANDOM_GENERATOR (Singleton<RandomSingleton>::getInstance())

}

#endif // !GLOBAL_HDR
