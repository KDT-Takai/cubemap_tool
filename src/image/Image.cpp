#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.hpp"
#include "Logger/Logger.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

// コンストラクタ
Image::Image(int w, int h)
    : width(w), height(h)
{
    data.resize(width * height * Channels);
}

Image::Image(const std::string& filepath) : width(0), height(0)
{
    load(filepath);
}

// 画像読み込み
bool Image::load(const std::string& filepath)
{
    int w, h, c;

    unsigned char* img = stbi_load(
        filepath.c_str(),
        &w,
        &h,
        &c,
        Channels
    );

    if (!img) {
        Log::error("Failed to load image: " + filepath);
        return false;
    }

    width = w;
    height = h;
    data.resize(width * height * Channels);

    std::memcpy(data.data(), img, data.size());
    stbi_image_free(img);
    
    Log::error("Image loaded successfully: " + filepath);

    return true;
}

// PNG 保存
bool Image::save(const std::string& filepath) const
{
    if (data.empty() || width == 0 || height == 0) {
        return false;
    }

    int stride = width * Channels;
    int result = stbi_write_png(
        filepath.c_str(),
        width,
        height,
        Channels,
        data.data(),
        stride
    );

    return result != 0;
}

// ピクセル取得
Pixel Image::getPixel(int x, int y) const
{
    x = std::clamp(x, 0, width - 1);
    y = std::clamp(y, 0, height - 1);

    int index = (y * width + x) * Channels;

    return Pixel{
        data[index + 0],
        data[index + 1],
        data[index + 2],
        data[index + 3]
    };
}

// ピクセル書き込み
void Image::setPixel(int x, int y, const Pixel& p)
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    int index = (y * width + x) * Channels;

    data[index + 0] = p.r;
    data[index + 1] = p.g;
    data[index + 2] = p.b;
    data[index + 3] = p.a;
}

// UVサンプリング
Pixel Image::sample(float u, float v) const
{
    u = std::clamp(u, 0.0f, 1.0f);
    v = std::clamp(v, 0.0f, 1.0f);

    float x = u * (width - 1);
    float y = v * (height - 1);

    int x0 = static_cast<int>(std::floor(x));
    int y0 = static_cast<int>(std::floor(y));
    int x1 = std::min(x0 + 1, width - 1);
    int y1 = std::min(y0 + 1, height - 1);

    float tx = x - x0;
    float ty = y - y0;

    Pixel p00 = getPixel(x0, y0);
    Pixel p10 = getPixel(x1, y0);
    Pixel p01 = getPixel(x0, y1);
    Pixel p11 = getPixel(x1, y1);

    auto lerp = [](uint8_t a, uint8_t b, float t) -> float {
        return a + (b - a) * t;
        };

    Pixel result;
    result.r = static_cast<uint8_t>(
        lerp(
            lerp(p00.r, p10.r, tx),
            lerp(p01.r, p11.r, tx),
            ty
        )
        );
    result.g = static_cast<uint8_t>(
        lerp(
            lerp(p00.g, p10.g, tx),
            lerp(p01.g, p11.g, tx),
            ty
        )
        );
    result.b = static_cast<uint8_t>(
        lerp(
            lerp(p00.b, p10.b, tx),
            lerp(p01.b, p11.b, tx),
            ty
        )
        );
    result.a = static_cast<uint8_t>(
        lerp(
            lerp(p00.a, p10.a, tx),
            lerp(p01.a, p11.a, tx),
            ty
        )
        );

    return result;
}