#ifndef GRASSLAND_BIOME_HDR
#define GRASSLAND_BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"
#include "Biome.h"

namespace acid 
{
    class GrasslandBiome : public Biome
    {
    public:
        GrasslandBiome(int seed);
        virtual ~GrasslandBiome() = default;

        virtual BlockID getPlant(Random<std::minstd_rand>& rand) const override;
        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const;

    private:
        virtual NoiseParameters getNoiseParameters();
    };
}

#endif // !GRASSLAND_BIOME_HDR
