#pragma once
#include "Canvas.h"
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

    glm::vec3 operator*(float distance) const {
        return GetPoint(distance);
    }
};

class Canvas;

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
    
    void PresentCanvas(const Canvas& canvas);

    friend class Canvas;

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;
};