#pragma once
#include <glm/glm.hpp>

namespace ray
{
    struct ray_t {
        ray_t() = default;
        ray_t(const glm::vec3& origin, const glm::vec3& direction) :
            origin(origin),
            direction(glm::normalize(direction)) // Normalize the direction vector
        {}

        glm::vec3 GetPoint(float distance) const {
            return origin + distance * direction;
        }

        glm::vec3 origin;
        glm::vec3 direction;

        // For the Extra Credit
        glm::vec3 operator*(float distance) const {
            return GetPoint(distance);
        }
    };
}