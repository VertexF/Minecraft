#include "Frustum.h"

namespace acid 
{
    Plane::Plane() : distanceToOrigin(0), normal(glm::vec3())
    {
    }

    float Plane::distanceToPoint(const glm::vec3& point) const 
    {
        return glm::dot(point, normal) + distanceToOrigin;
    }

    void ViewFrustum::update(const glm::mat4& projectionViewMatrix) noexcept
    {
        //Left
        _planes.at(Planes::LEFT).normal.x = projectionViewMatrix[0][3] + projectionViewMatrix[0][0];
        _planes.at(Planes::LEFT).normal.y = projectionViewMatrix[1][3] + projectionViewMatrix[1][0];
        _planes.at(Planes::LEFT).normal.z = projectionViewMatrix[2][3] + projectionViewMatrix[2][0];
        _planes.at(Planes::LEFT).distanceToOrigin = projectionViewMatrix[3][3] + projectionViewMatrix[3][0];

        //Right
        _planes.at(Planes::RIGHT).normal.x = projectionViewMatrix[0][3] - projectionViewMatrix[0][0];
        _planes.at(Planes::RIGHT).normal.y = projectionViewMatrix[1][3] - projectionViewMatrix[1][0];
        _planes.at(Planes::RIGHT).normal.z = projectionViewMatrix[2][3] - projectionViewMatrix[2][0];
        _planes.at(Planes::RIGHT).distanceToOrigin = projectionViewMatrix[3][3] - projectionViewMatrix[3][0];

        //Bottom
        _planes.at(Planes::BOTTOM).normal.x = projectionViewMatrix[0][3] + projectionViewMatrix[0][1];
        _planes.at(Planes::BOTTOM).normal.y = projectionViewMatrix[1][3] + projectionViewMatrix[1][1];
        _planes.at(Planes::BOTTOM).normal.z = projectionViewMatrix[2][3] + projectionViewMatrix[2][1];
        _planes.at(Planes::BOTTOM).distanceToOrigin = projectionViewMatrix[3][3] + projectionViewMatrix[3][1];

        //Top
        _planes.at(Planes::TOP).normal.x = projectionViewMatrix[0][3] - projectionViewMatrix[0][1];
        _planes.at(Planes::TOP).normal.y = projectionViewMatrix[1][3] - projectionViewMatrix[1][1];
        _planes.at(Planes::TOP).normal.z = projectionViewMatrix[2][3] - projectionViewMatrix[2][1];
        _planes.at(Planes::TOP).distanceToOrigin = projectionViewMatrix[3][3] - projectionViewMatrix[3][1];

        //Near
        _planes.at(Planes::NEAR).normal.x = projectionViewMatrix[0][3] + projectionViewMatrix[0][2];
        _planes.at(Planes::NEAR).normal.y = projectionViewMatrix[1][3] + projectionViewMatrix[1][2];
        _planes.at(Planes::NEAR).normal.z = projectionViewMatrix[2][3] + projectionViewMatrix[2][2];
        _planes.at(Planes::NEAR).distanceToOrigin = projectionViewMatrix[3][3] + projectionViewMatrix[3][2];

        //Far
        _planes.at(Planes::FAR).normal.x = projectionViewMatrix[0][3] - projectionViewMatrix[0][2];
        _planes.at(Planes::FAR).normal.y = projectionViewMatrix[1][3] - projectionViewMatrix[1][2];
        _planes.at(Planes::FAR).normal.z = projectionViewMatrix[2][3] - projectionViewMatrix[2][2];
        _planes.at(Planes::FAR).distanceToOrigin = projectionViewMatrix[3][3] - projectionViewMatrix[3][2];

        for (auto& plane : _planes) 
        {
            float length = glm::length(plane.normal);
            plane.normal /= length;
            plane.distanceToOrigin /= length;
        }
    }
}