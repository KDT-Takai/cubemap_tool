#include "Cubemap.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Cubemap::Cubemap(int faceSize)
    : m_faceSize(faceSize) {

    m_faces.reserve(6);
    for (int i = 0; i < 6; ++i) {
        m_faces.emplace_back(faceSize, faceSize);
    }
}

Image& Cubemap::getFace(FaceIndex face) {
    return m_faces[static_cast<int>(face)];
}

const Image& Cubemap::getFace(FaceIndex face) const {
    return m_faces[static_cast<int>(face)];
}

int Cubemap::getFaceSize() const {
    return m_faceSize;
}

void Cubemap::saveSeparateFaces(const std::string& basePath) const {
    const std::array<std::string, 6> suffixes = {
        "_px", "_nx", // Right, Left
        "_py", "_ny", // Top, Bottom
        "_pz", "_nz"  // Front, Back
    };

    fs::path pathObj(basePath);
    std::string stem = pathObj.stem().string();       // 拡張子なしのファイル名
    std::string ext = pathObj.extension().string();   // 拡張子 (.pngなど)
    fs::path parent = pathObj.parent_path();          // 保存先フォルダ

    for (int i = 0; i < 6; ++i) {
        std::string filename = stem + suffixes[i] + ext;
        fs::path fullPath = parent / filename;

        const Image& faceImg = m_faces[i];

        if (faceImg.save(fullPath.string())) {
            std::cout << "[Info] Saved face: " << fullPath.string() << "\n";
        }
        else {
            std::cerr << "[Error] Failed to save face: " << fullPath.string() << "\n";
        }
    }
}