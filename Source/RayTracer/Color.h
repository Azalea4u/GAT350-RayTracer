#pragma once
#include <glm/glm.hpp>

using color3_t = glm::vec3;
using color4_t = glm::vec4;

using rgba_t = uint32_t;


inline color4_t RGBAToColor(const rgba_t& rgba) {
    return color4_t(
        ((rgba >> 24) & 0xFF) / 255.0f, // Red
        ((rgba >> 16) & 0xFF) / 255.0f, // Green
        ((rgba >> 8) & 0xFF) / 255.0f,  // Blue
        (rgba & 0xFF) / 255.0f          // Alpha
    );
}

inline rgba_t ColorToRGBA(const color4_t& color) {
    return
        (static_cast<rgba_t>(color.r * 255) << 24) |
        (static_cast<rgba_t>(color.g * 255) << 16) |
        (static_cast<rgba_t>(color.b * 255) << 8) |
        static_cast<rgba_t>(color.a * 255);
}
