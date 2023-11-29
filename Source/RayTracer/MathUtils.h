#pragma once

namespace ray
{
    template <typename T>
    inline T lerp(const T& a, const T& b, float t) {
        // lerp(a, b, t) = a + t * (b - a)
        return a + t * (b - a);
        // return (a * (1 - t)) + (t * b);
    }
}