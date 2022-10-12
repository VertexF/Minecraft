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

    //This is needed for the custom hasher to work with an std::unordered_map data structure.
    bool operator==(const VectorXZ& lhs, const VectorXZ& rhs) noexcept;
    bool operator==(const sf::Vector3i& lhs, const sf::Vector3i& rhs) noexcept;

    template<typename T>
    struct hash
    {
    };

    template<>
    struct hash<VectorXZ>
    {
        std::size_t operator()(const VectorXZ& vector) const noexcept
        {
            auto hash1 = std::hash<int>{}(vector.x);
            auto hash2 = std::hash<int>{}(vector.z);

            return std::hash<int>{}(hash1 ^ hash2) >> 2;
        }
    };

    template<>
    struct hash<sf::Vector3i>
    {
        std::size_t operator()(const sf::Vector3i& vector) const noexcept
        {
            auto hash1 = std::hash<decltype(vector.x)>{}(vector.x);
            auto hash2 = std::hash<decltype(vector.x)>{}(vector.y);
            auto hash3 = std::hash<decltype(vector.x)>{}(vector.z);

            return std::hash<decltype(vector.x)>{}(hash1 ^ (hash2 << hash3) ^ hash3);
        }
    };
}

#endif // !VECTOR2XZ_HDR
