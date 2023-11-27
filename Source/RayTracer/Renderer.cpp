#include "Renderer.h"
#include <iostream>

bool Renderer::Initialize() // Corrected the method name
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Shutdown()
{
    if (m_window != nullptr) // Corrected the variable name
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if (m_renderer != nullptr) // Corrected the variable name
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
