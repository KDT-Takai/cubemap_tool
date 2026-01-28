#pragma once
#include "cubemap/Cubemap.hpp"
#include "image/Image.hpp"

class DiceLayout {
public:
    // Cubemap‚ğó‚¯æ‚èA“WŠJ}(Image)‚ğ•Ô‚·
    static Image generate(const Cubemap& source);
};