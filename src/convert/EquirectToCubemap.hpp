#pragma once
#include "image/Image.hpp"
#include "cubemap/Cubemap.hpp"
#include "FaceBasis/FaceBasis.hpp"

class EquirectToCubemap {
public:
    static const FaceBasis* const s_faceBasis;
    static Cubemap convert(Image source, int faceSize, bool force, bool resize);
};