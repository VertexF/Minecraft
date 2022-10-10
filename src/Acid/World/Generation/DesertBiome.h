#ifndef DESERT_BIOME_HDR
#define DESERT_BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"
#include "Biome.h"

namespace acid 
{
    class DesertBoime : public Biome
    {
    public:
        DesertBoime(int seed);
        virtual ~DesertBoime() = default;

        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;

    private:
        virtual NoiseParameters getNoiseParameters() override;
    };
}

#endif // !DESERT_BIOME_HDR
