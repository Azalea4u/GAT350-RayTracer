#include "Canvas.h"
#include "Renderer.h"
#include <algorithm>
Canvas::Canvas(int width, int height, const Renderer& renderer)
{
    m_size = glm::ivec2(width, height);
    m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    m_buffer.resize(width * height);
}

Canvas::~Canvas()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
    }
}

void Canvas::Update()
{
    SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_size.x * sizeof(rgba_t));
}

void Canvas::Clear(const color4_t& color)
{
    rgba_t rgba = ColorToRGBA(color);
    std::fill(m_buffer.begin(), m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
    // copy canvas texture to renderer
    if (point.x >= m_size.x || point.x < 0 || point.y >= m_size.y || point.y > 0) return;
    // present renderer to screen
    m_buffer[point.x + (point.y * m_size.x)] = ColorToRGBA(color);
}
