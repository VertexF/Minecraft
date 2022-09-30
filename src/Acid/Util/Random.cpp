#include "Random.h"

namespace acid 
{
    RandomSingleton::RandomSingleton() 
    {
        _randomEngine.seed(std::time(nullptr));
        for (int i = 0; i < 5; i++) 
        {
            intInRange(i, i * 5);
        }
    }
}