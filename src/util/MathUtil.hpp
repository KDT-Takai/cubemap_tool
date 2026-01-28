#pragma once
#include <cmath>
#include <numbers>

namespace MathUtil {
    constexpr float PI = std::numbers::pi_v<float>;

    struct Vec3 {
        float x, y, z;

        // ƒxƒNƒgƒ‹‚Ì³‹K‰»
        Vec3 normalized() const {
            float len = std::sqrt(x * x + y * y + z * z);
            if (len == 0.0f) return { 0, 0, 0 };
            return { x / len, y / len, z / len };
        }
    };
}