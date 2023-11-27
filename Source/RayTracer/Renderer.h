#pragma once
#include <string>
#include <SDL.h>
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

    // Operator overload for multiplying a ray by a float
    glm::vec3 operator*(float distance) const {
        return GetPoint(distance);
    }
};

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};