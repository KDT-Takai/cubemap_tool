#include "EquirectToCubemap.hpp"
#include "util/MathUtil.hpp"
#include "Logger/Logger.hpp"
#include <cmath>

using namespace MathUtil;

const FaceBasis* const EquirectToCubemap::s_faceBasis = new FaceBasis[6]{
    {{1,0,0}, {0,0,-1}, {0,-1,0}},   // +X
    {{-1,0,0}, {0,0,1}, {0,-1,0}},   // -X
    {{0,1,0}, {1,0,0}, {0,0,1}},     // +Y
    {{0,-1,0}, {1,0,0}, {0,0,-1}},   // -Y
    {{0,0,1}, {1,0,0}, {0,-1,0}},    // +Z
    {{0,0,-1}, {-1,0,0}, {0,-1,0}}   // -Z
};

Cubemap EquirectToCubemap::convert(Image source, int faceSize, bool force, bool resize) {
    if (source.width <= 0 || source.height <= 0) {
        throw std::runtime_error("Source image is empty");
    }

    if (faceSize <= 0 || faceSize > 4096) {
        throw std::runtime_error("Invalid face size");
    }

    float aspect = float(source.width) / float(source.height);

    if (std::abs(aspect - 2.0f) > 0.01f) {

        if (resize) {
            Logger::warn("Resizing image to 2:1 aspect ratio");

            int newHeight = source.height;
            int newWidth = newHeight * 2;

            source = source.resized(newWidth, newHeight);
        }
        else if (!force) {
            throw std::runtime_error("Input image is not equirectangular");
        }
        else {
            Logger::warn("Force converting non-2:1 image (distortion expected)");
        }
    }

    Cubemap cubemap(faceSize);

    for (int i = 0; i < 6; ++i) {
        FaceIndex faceIdx = static_cast<FaceIndex>(i);
        Image& faceImg = cubemap.getFace(faceIdx);
        const FaceBasis& face = s_faceBasis[i];

        for (int y = 0; y < faceSize; ++y) {
            for (int x = 0; x < faceSize; ++x) {
                float nx = (x + 0.5f) / faceSize * 2.0f - 1.0f;
                float ny = (y + 0.5f) / faceSize * 2.0f - 1.0f;

                Vec3 dir = (face.normal + face.u * nx + face.v * ny).normalized();

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