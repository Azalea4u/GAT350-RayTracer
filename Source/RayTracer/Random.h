#pragma once
#include <cstdlib>
#include <algorithm>

inline void seedRandom(unsigned int seed) {
    srand(seed);
}

inline float random01() {
    return static_cast<float>(rand()) / RAND_MAX;
}

inline float random(float min, float max) {
    if (min > max) std::swap(min, max);
    return min + (max - min) * random01();
}
