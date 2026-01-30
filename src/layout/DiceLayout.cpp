#include "DiceLayout.hpp"
#include "Logger/Logger.hpp"

Image DiceLayout::generate(const Cubemap& cube, DiceLayoutPreset preset)
{
    switch (preset) {
    case DiceLayoutPreset::CrossHorizontal:
        return generateCrossHorizontal(cube);

    case DiceLayoutPreset::CrossVertical:
        return generateCrossVertical(cube);

    case DiceLayoutPreset::Horizontal:
        return generateHorizontal(cube);

    case DiceLayoutPreset::Vertical:
        return generateVertical(cube);
    }
    Logger::error("not found Preset");
    return generateCrossHorizontal(cube);
}

Image DiceLayout::generateCrossHorizontal(const Cubemap& cube)
{
    int s = cube.getFaceSize();
    Image out(s * 4, s * 3);

    out.blit(cube.getFace(FaceIndex::PosY), s, 0);
    out.blit(cube.getFace(FaceIndex::NegX), 0, s);
    out.blit(cube.getFace(FaceIndex::PosZ), s, s);
    out.blit(cube.getFace(FaceIndex::PosX), s * 2, s);
    out.blit(cube.getFace(FaceIndex::NegZ), s * 3, s);
    out.blit(cube.getFace(FaceIndex::NegY), s, s * 2);

    return out;
}

Image DiceLayout::generateCrossVertical(const Cubemap& cube)
{
    const int s = cube.getFaceSize();
    Image out(s * 3, s * 4);

    out.blit(cube.getFace(FaceIndex::PosY), s, 0);      // è„
    out.blit(cube.getFace(FaceIndex::PosZ), s, s);      // íÜâõ
    out.blit(cube.getFace(FaceIndex::PosX), s * 2, s);  // âE
    out.blit(cube.getFace(FaceIndex::NegX), 0, s);      // ç∂
    out.blit(cube.getFace(FaceIndex::NegY), s, s * 2);  // â∫
    out.blit(cube.getFace(FaceIndex::NegZ), s, s * 3);  // ç≈â∫íi

    return out;
}

Image DiceLayout::generateHorizontal(const Cubemap& cube)
{
    int s = cube.getFaceSize();

    Image out(s * 6, s);

    FaceIndex order[6] = {
        FaceIndex::PosX,
        FaceIndex::NegX,
        FaceIndex::PosY,
        FaceIndex::NegY,
        FaceIndex::PosZ,
        FaceIndex::NegZ
    };

    for (int i = 0; i < 6; ++i) {
        out.blit(cube.getFace(order[i]), i * s, 0);
    }

    return out;
}

Image DiceLayout::generateVertical(const Cubemap& cube)
{
    int s = cube.getFaceSize();

    Image out(s, s * 6);

    FaceIndex order[6] = {
        FaceIndex::PosX,
        FaceIndex::NegX,
        FaceIndex::PosY,
        FaceIndex::NegY,
        FaceIndex::PosZ,
        FaceIndex::NegZ
    };

    for (int i = 0; i < 6; ++i) {
        out.blit(cube.getFace(order[i]), 0, i * s);
    }

    return out;
}