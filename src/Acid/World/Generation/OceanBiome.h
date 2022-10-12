#ifndef OCEAN_BIOME_HDR
#define OCAEN_BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"
#include "Biome.h"

namespace acid 
{
    class OceanBiome : public Biome
    {
    public:
        OceanBiome(int seed);
        virtual ~OceanBiome() = default;

        virtual BlockID getPlant(Random<std::minstd_rand>& rand) const override;
        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;

    private:
        virtual NoiseParameters getNoiseParameters() override;
    };
}

#endif // !OCEAN_BIOME_HDR
