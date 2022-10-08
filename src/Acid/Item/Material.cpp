#include "Material.h"

namespace acid 
{
    const Material Material::NOTHING_BLOCK(Material::ID::NOTHING, 0, false, "None");
    const Material Material::GRASS_BLOCK(Material::ID::GRASS, 99, true, "Grass Block");
    const Material Material::DIRT_BLOCK(Material::ID::DIRT, 99, true, "Dirt Block");
    const Material Material::STONE_BLOCK(Material::ID::STONE, 99, true, "Stone Block");
    const Material Material::OAK_BARK_BLOCK(Material::ID::OAK_BARK, 99, true, "Oak Bark Block");
    const Material Material::OAK_LEAF_BLOCK(Material::ID::OAK_LEAF, 99, true, "Oak Leaf Block");

    Material::Material(Material::ID id, int maxStack, bool isBlock, std::string&& name) :
        id(id), maxStackSize(maxStack), isBlock(isBlock), name(std::move(name))
    {
    }

    BlockID Material::toBlockID() const 
    {
        switch (id) 
        {
        case ID::NOTHING:
            return BlockID::AIR;
        case ID::GRASS:
            return BlockID::GRASS;
        case ID::DIRT:
            return BlockID::DIRT;
        case ID::STONE:
            return BlockID::STONE;
        case ID::OAK_BARK:
            return BlockID::OAK_BARK;
        case ID::OAK_LEAF:
            return BlockID::OAK_LEAF;
        defualt:
            return BlockID::NUM_TYPES;
        }
    }

    const Material& Material::toMaterial(BlockID id)
    {
        switch (id)
        {
        case BlockID::AIR:
            return NOTHING_BLOCK;
        case BlockID::GRASS:
            return GRASS_BLOCK;
        case BlockID::DIRT:
            return DIRT_BLOCK;
        case BlockID::STONE:
            return STONE_BLOCK;
        case BlockID::OAK_BARK:
            return OAK_BARK_BLOCK;
        case BlockID::OAK_LEAF:
            return OAK_LEAF_BLOCK;
        }
    }
}