#include "Material.h"

namespace acid 
{
    const Material Material::NOTHING_BLOCK(Material::ID::NOTHING, 0, false, "None");
    const Material Material::GRASS_BLOCK(Material::ID::GRASS, 99, true, "Grass Block");
    const Material Material::DIRT_BLOCK(Material::ID::DIRT, 99, true, "Dirt Block");
    const Material Material::STONE_BLOCK(Material::ID::STONE, 99, true, "Stone Block");
    const Material Material::OAK_BARK_BLOCK(Material::ID::OAK_BARK, 99, true, "Oak Bark Block");
    const Material Material::OAK_LEAF_BLOCK(Material::ID::OAK_LEAF, 99, true, "Oak Leaf Block");
    const Material Material::SAND_BLOCK(Material::ID::SAND, 99, true, "Sand Block");
    const Material Material::CACTUS_BLOCK(Material::ID::CACTUS, 99, true, "Cactus Block");
    const Material Material::ROSE_FLOWER(Material::ID::OAK_LEAF, 99, true, "Rose");
    const Material Material::DEAD_SHRUB(Material::ID::SAND, 99, true, "Dead Shrub");
    const Material Material::TALL_GRASS(Material::ID::CACTUS, 99, true, "Tall Grass");

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
        case ID::SAND:
            return BlockID::SAND;
        case ID::CACTUS:
            return BlockID::CACTUS;
        case ID::ROSE:
            return BlockID::ROSE;
        case ID::DEADSHRUB:
            return BlockID::DEADSHRUB;
        case ID::TALLGRASS:
            return BlockID::TALLGRASS;
        default:
            return BlockID::NUM_TYPES;
        }
    }

    const Material& Material::toMaterial(BlockID id)
    {
        switch (id)
        {
        case BlockID::NUM_TYPES:
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
        case BlockID::SAND:
            return SAND_BLOCK;
        case BlockID::CACTUS:
            return CACTUS_BLOCK;
        case BlockID::ROSE:
            return ROSE_FLOWER;
        case BlockID::DEADSHRUB:
            return DEAD_SHRUB;
        case BlockID::TALLGRASS:
            return TALL_GRASS;
        default:
            return NOTHING_BLOCK;
        }
    }
}