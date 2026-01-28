#pragma once
#include <string>
#include <vector>

struct Pixel {
    uint8_t r, g, b, a;

    Pixel() : r(0), g(0), b(0), a(255) {}

    Pixel(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
        : r(_r), g(_g), b(_b), a(_a) {
    }
};
class Image {
public:
    int width = 0;
    int height = 0;
    static constexpr int Channels = 4;
    std::vector<uint8_t> data;

    Image() = default;
    Image(int w, int h);
    Image(const std::string& filepath);

    bool load(const std::string& filepath);
    bool save(const std::string& filepath) const;

    Pixel sample(float u, float v) const;

    void setPixel(int x, int y, const Pixel& p);

    Pixel getPixel(int x, int y) const;
};