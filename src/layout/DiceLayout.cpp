#include "DiceLayout.hpp"

Image DiceLayout::generate(const Cubemap& source) {
    int fs = source.getFaceSize();

    int outW = fs * 3;
    int outH = fs * 4;

    Image canvas(outW, outH);

    auto copyFace = [&](FaceIndex face, int gridX, int gridY) {
        const Image& srcFace = source.getFace(face);

        for (int y = 0; y < fs; ++y) {
            for (int x = 0; x < fs; ++x) {
                Pixel p = srcFace.getPixel(x, y);

                // キャンバス上の書き込み位置
                int destX = gridX * fs + x;
                int destY = gridY * fs + y;

                canvas.setPixel(destX, destY, p);
            }
        }
        };

    copyFace(FaceIndex::PosY, 1, 0); // Top
    copyFace(FaceIndex::NegX, 0, 1); // Left
    copyFace(FaceIndex::PosZ, 1, 1); // Front
    copyFace(FaceIndex::PosX, 2, 1); // Right
    copyFace(FaceIndex::NegY, 1, 2); // Bottom
    copyFace(FaceIndex::NegZ, 1, 3); // Back

    return canvas;
}