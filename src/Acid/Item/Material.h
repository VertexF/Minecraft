#ifndef MATERIAL_HDR
#define MATERIAL_HDR

#include <functional>
#include <string>
#include "../World/Block/BlockID.h"

namespace acid 
{
    struct Material 
    {
        enum class ID 
        {
            NOTHING,
            GRASS,
            DIRT,
            STONE,
            OAK_BARK,
            OAK_LEAF,
            SAND,
            CACTUS
        };

        const static Material NOTHING_BLOCK, GRASS_BLOCK, DIRT_BLOCK, STONE_BLOCK, OAK_BARK_BLOCK, OAK_LEAF_BLOCK, SAND_BLOCK, CACTUS_BLOCK;

        Material(Material::ID id, int maxStack, bool isBlock, std::string&& name);

        BlockID toBlockID() const;
        static const Material& toMaterial(BlockID id);

        const Material::ID id;
        const int maxStackSize;
        const bool isBlock;
        const std::string name;
    };

    template<typename T>
    struct stringHash 
    {
    };

    template<>
    struct stringHash<Material::ID>
    {
        std::size_t operator()(const Material::ID& id) const 
        {
            std::hash<Material::ID> hasher;
            return hasher(id);
        }
    };
}

#endif // !MATERIAL_HDR
