#ifndef QUAD_RENDERER_HDR
#define QUAD_RENDERER_HDR

#include <vector>
#include <glm/glm.hpp>

#include "../Source/Model.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"

namespace acid 
{
    class Camera;

    class QuadRenderer 
    {
    public:
        QuadRenderer();

        void add(const glm::vec3& position);
        void renderQuads(const Camera& camera);
    private:
        std::vector<glm::vec3> _quads;

        Model _quadModel;
        BasicShader _shader;
        BasicTexture _basicTexture;
    };
}

#endif // !QUAD_RENDERER_HDR
