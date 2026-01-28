#pragma once
#include "image/Image.hpp"
#include "cubemap/Cubemap.hpp"

class EquirectToCubemap {
public:
    // Equirect画像を受け取り、指定サイズのCubemapを生成して返す
    static Cubemap convert(const Image& source, int faceSize);
};