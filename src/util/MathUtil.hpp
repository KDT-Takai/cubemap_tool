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

    inline Vec3 operator+(const Vec3& a, const Vec3& b) {
        return { a.x + b.x, a.y + b.y, a.z + b.z };
    }

    inline Vec3 operator-(const Vec3& a, const Vec3& b) {
        return { a.x - b.x, a.y - b.y, a.z - b.z };
    }

    inline Vec3 operator*(const Vec3& v, float s) {
        return { v.x * s, v.y * s, v.z * s };
    }

    inline Vec3 operator*(float s, const Vec3& v) {
        return v * s;
    }
}