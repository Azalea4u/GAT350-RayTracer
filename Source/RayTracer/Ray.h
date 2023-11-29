#pragma once
#include <glm/glm.hpp>

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;

    Ray() = default;
    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin(origin), direction(glm::normalize(direction)) {}

    glm::vec3 GetPoint(float distance) const {
        return origin + distance * direction;
    }

    glm::vec3 operator*(float distance) const {
        return GetPoint(distance);
    }
};