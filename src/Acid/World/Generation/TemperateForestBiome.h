#ifndef TEMPERATE_FOREST_BIOME_HDR
#define TEMPERATE_FOREST_BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"
#include "Biome.h"

namespace acid 
{
    class TemperateForestBiome : public Biome
    {
    public:
        TemperateForestBiome(int seed);
        virtual ~TemperateForestBiome() = default;

        virtual BlockID getPlant(Random<std::minstd_rand>& rand) const override;
        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;
    private:
        virtual NoiseParameters getNoiseParameters() override;
    };
}

#endif // !TEMPERATE_FOREST_BIOME_HDR
