#pragma once
#include "cubemap/Cubemap.hpp"
#include "image/Image.hpp"

enum class DiceLayoutPreset {
    CrossHorizontal,          // ‰¡\šŒ^
	CrossVertical,  // c\šŒ^
    Horizontal,     // ‰¡ˆê—ñ
    Vertical        // cˆê—ñ
};

class DiceLayout {
public:
    static Image generate(const Cubemap& cube, DiceLayoutPreset preset);
private:
    static Image generateCrossHorizontal(const Cubemap& cube);
    static Image generateCrossVertical(const Cubemap& cube);
    static Image generateHorizontal(const Cubemap& cube);
    static Image generateVertical(const Cubemap& cube);
};