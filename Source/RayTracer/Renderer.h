#pragma once
#include <SDL.h>
#include <string>

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