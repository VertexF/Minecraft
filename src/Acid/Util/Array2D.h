#ifndef ARRAY_2D_HDR
#define ARRAY_2D_HDR

#include <array>
#include <algorithm>

namespace acid 
{
    template<typename T, int WIDTH>
    class Array2D 
    {
    public:
        T& get(int x, int z)
        {
            return _array.at(x * WIDTH + z);
        }

        const T& get(int x, int z) const
        {
            return _array.at(x * WIDTH + z);
        }

        T& getMaxValue() 
        {
            return *std::max_element(_array.begin(), _array.end());
        }
    private:
        std::array<T, WIDTH* WIDTH> _array;
    };
}

#endif // !ARRAY_2D_HDR
