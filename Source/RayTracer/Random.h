#pragma once

#include <cstdlib>  // For rand and srand
#include <algorithm> // For std::swap

namespace ray
{
    // Seed the random number generator
    inline void seedRandom(unsigned int seed) {
        std::srand(seed);
    }

    // Generate a random float between 0 and 1
    inline float random01() {
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    // Generate a random float between min and max
    inline float random(float min, float max) {
        if (min > max) {
            std::swap(min, max);
        }
        return min + (max - min) * random01();
    }
}
