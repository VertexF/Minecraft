#ifndef RANDOM_HDR
#define RANDOM_HDR

#include <random>
#include <ctime>

#include "Singleton.h"

namespace acid 
{
    //This is wrapped in the templated singleton class. So it's a singleton if you use correctly.
    class RandomSingleton 
    {
    public:
        RandomSingleton();

        template<typename T>
        T intInRange(T low, T high) 
        {
            static_assert(std::is_integral<T>::value, "Not a integral type!!");
            std::uniform_int_distribution<T> dist(low, high);
            return dist(_randomEngine);
        }
    private:

        std::mt19937 _randomEngine;
    };

    template<typename REngine = std::mt19937>
    class Random 
    {
    public:
        Random(int n = std::time(nullptr))
        {
            _randomEngine.seed(n);
            for (int i = 0; i < 5; i++) 
            {
                intInRange(i, i * 5);
            }
        }

        template<typename T>
        T intInRange(T low, T high) 
        {
            static_assert(std::is_integral<T>::value, "Not a integral type!!");
            std::uniform_int_distribution<T> dist(low, high);
            return dist(_randomEngine);
        }

    private:
        REngine _randomEngine;
    };
}

#endif // !RANDOM_HDR
