#ifndef VECTOR2XZ_HDR
#define VECTOR2XZ_HDR

#include <functional>
#include <type_traits>
#include <SFML/Graphics.hpp>

namespace acid 
{
    struct VectorXZ 
    {
        int x, z;
    };

    bool operator==(const VectorXZ& left, const VectorXZ& right);

    template<typename T>
    struct hash
    {
    };

    template<>
    struct hash<VectorXZ>
    {
        std::size_t operator()(const VectorXZ& vector) const 
        {
            std::hash<decltype(vector.x)> hasher;

            auto hash1 = hasher(vector.x);
            auto hash2 = hasher(vector.z);

            return std::hash<decltype(vector.x)>{}((hash1 ^ hash2) >> 2);
        }
    };

    template<>
    struct hash<sf::Vector3i>
    {
        std::size_t operator()(const sf::Vector3i& vector) const
        {
            std::hash<decltype(vector.x)> hasher;

            auto hash1 = hasher(vector.x);
            auto hash2 = hasher(vector.y);
            auto hash3 = hasher(vector.z);

            return std::hash<decltype(vector.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}

#endif // !VECTOR2XZ_HDR
