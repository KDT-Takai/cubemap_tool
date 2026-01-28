#pragma once
#include <vector>
#include <string>
#include <array>
#include "image/Image.hpp"

enum class FaceIndex {
    PosX = 0, // +X (Right)
    NegX = 1, // -X (Left)
    PosY = 2, // +Y (Top)
    NegY = 3, // -Y (Bottom)
    PosZ = 4, // +Z (Front)
    NegZ = 5, // -Z (Back)
    Count = 6
};

class Cubemap {
public:
    explicit Cubemap(int faceSize);

    Image& getFace(FaceIndex face);

    const Image& getFace(FaceIndex face) const;

    int getFaceSize() const;

    void saveSeparateFaces(const std::string& basePath) const;

private:
    int m_faceSize;
    std::vector<Image> m_faces; // 6–‡‚Ì‰æ‘œ‚ğ•Û
};