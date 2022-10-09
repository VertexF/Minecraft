#ifndef BIOME_HDR
#define BIOME_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockID.h"

namespace acid 
{
    class Chunk;

    struct IBoime 
    {
        virtual ~IBoime() = default;
        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const = 0;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const = 0;

        virtual int getHeight(int x, int z, int chunkX, int chunkZ) const = 0;
        virtual int getTreeFrequency() const = 0;
    };

    class GrasslandBiome : public IBoime 
    {
    public:
        GrasslandBiome(int seed);
        virtual ~GrasslandBiome() = default;

        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;

        virtual int getHeight(int x, int z, int chunkX, int chunkZ) const override;
        virtual int getTreeFrequency() const override;
    private:
        NoiseGenerator _heightGenerator;
    };

    class LightForestBiome : public IBoime
    {
    public:
        LightForestBiome(int seed);
        virtual ~LightForestBiome() = default;

        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;

        virtual int getHeight(int x, int z, int chunkX, int chunkZ) const override;
        virtual int getTreeFrequency() const override;
    private:
        NoiseGenerator _heightGenerator;
    };

    class DesertBoime : public IBoime
    {
    public:
        DesertBoime(int seed);
        virtual ~DesertBoime() = default;

        virtual BlockID getTopBlock(Random<std::minstd_rand>& rand) const override;
        virtual void makeTree(Random<std::minstd_rand>& rand, Chunk& chunk, int x, int y, int z) const override;

        virtual int getHeight(int x, int z, int chunkX, int chunkZ) const override;
        virtual int getTreeFrequency() const override;
    private:
        NoiseGenerator _heightGenerator;
    };
}

#endif // !BIOME_HDR
