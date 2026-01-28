#include "EquirectToCubemap.hpp"
#include "util/MathUtil.hpp"
#include <cmath>

using namespace MathUtil;

Cubemap EquirectToCubemap::convert(const Image& source, int faceSize) {
    Cubemap cubemap(faceSize);

    for (int i = 0; i < 6; ++i) {
        FaceIndex faceIdx = static_cast<FaceIndex>(i);
        Image& faceImg = cubemap.getFace(faceIdx);

        for (int y = 0; y < faceSize; ++y) {
            for (int x = 0; x < faceSize; ++x) {
                float nx = (x + 0.5f) / faceSize * 2.0f - 1.0f;
                float ny = (y + 0.5f) / faceSize * 2.0f - 1.0f;

                Vec3 dir = { 0, 0, 0 };

                switch (faceIdx) {
                case FaceIndex::PosX: dir = { 1.0f, -ny, -nx }; break;  // +X (Right)
                case FaceIndex::NegX: dir = { -1.0f, -ny,  nx }; break; // -X (Left)
                case FaceIndex::PosY: dir = { nx,  1.0f,  ny }; break;  // +Y (Top)
                case FaceIndex::NegY: dir = { nx, -1.0f, -ny }; break;  // -Y (Bottom)
                case FaceIndex::PosZ: dir = { nx, -ny,  1.0f }; break;  // +Z (Front)
                case FaceIndex::NegZ: dir = { -nx, -ny, -1.0f }; break; // -Z (Back)
                default: break;
                }

                dir = dir.normalized();

                float theta = std::atan2(dir.x, dir.z);
                float phi = std::asin(dir.y);

                float u = (theta + PI) / (2.0f * PI);
                float v = (phi + PI / 2.0f) / PI;

                Pixel p = source.sample(u, 1.0f - v);

                faceImg.setPixel(x, y, p);
            }
        }
    }

    return cubemap;
}