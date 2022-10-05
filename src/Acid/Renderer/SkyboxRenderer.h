#ifndef SKYBOX_RENDERER_HDR
#define SKYBOX_RENDERER_HDR

#include "../Shaders/SkyboxShader.h"
#include "../Texture/CubeTexture.h"
#include "../Source/Model.h"

namespace acid 
{
    class Camera;

    class SkyRenderer 
    {
    public:
        SkyRenderer();

        void render(const Camera& camera);

    private:
        Model _skyCude;
        SkyboxShader _shader;
        CubeTexture _cubeTexture;
    };
}

#endif // !SKYBOX_RENDERER_HDR
