#ifndef RAY_HDR
#define RAY_HDR

#include <glm/glm.hpp>

namespace acid 
{
    class Ray 
    {
    public:
        Ray(const glm::vec3& position, const glm::vec3& direction);

        void step(float scale);
        const glm::vec3& getEnd() const;
        float getLenght() const;
    private:
        glm::vec3 _rayStart;
        glm::vec3 _rayEnd;
        glm::vec3 _direction;
    };
}

#endif // !RAY_HDR
