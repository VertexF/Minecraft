#ifndef CUBE_RENDERER_HDR
#define CUBE_RENDERER_HDR

#include <vector>
#include <glm/glm.hpp>

#include "../Source/Model.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"
#include "../Texture/TextureAtlas.h"

namespace acid 
{
    class Camera;

    class CubeRenderer 
    {
    public:
        CubeRenderer();

        void add(const glm::vec3& position);
        void render(const Camera& camera);

    private:
        std::vector<glm::vec3> _cubes;

        Model _cubeModel;
        BasicShader _shader;
        BasicTexture _basicTexture;
        TextureAtlas _textureAtlas;
    };
}

#endif // !CUBE_RENDERER_HDR
