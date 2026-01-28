#include <iostream>
#include <string>
#include "Image/Image.hpp"
#include "cubemap/Cubemap.hpp"
#include "convert/EquirectToCubemap.hpp"
#include "layout/DiceLayout.hpp"
#include "Log/Log.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: cubemap_tool.exe input.png output.png [--facesize N]\n";
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];
    int faceSize = 512; // デフォルト

    // オプション解析（--facesize N）
    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--facesize" && i + 1 < argc) {
            faceSize = std::stoi(argv[++i]);
        }
    }

    Log::info("Loading input image: " + inputPath);
    Image src(inputPath);

    Log::info("Converting to cubemap...");
    Cubemap cube = EquirectToCubemap::convert(src, faceSize);

    Log::info("Generating dice layout...");
    Image dice = DiceLayout::generate(cube);

    Log::info("Saving output: " + outputPath);
    if (!dice.save(outputPath)) {
        Log::error("Failed to save output image: " + outputPath);
        return 1;
    }

    Log::info("Done!");
    return 0;
}
