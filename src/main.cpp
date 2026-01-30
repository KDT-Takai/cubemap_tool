#include <iostream>
#include <string>
#include <filesystem>

#include "Image/Image.hpp"
#include "cubemap/Cubemap.hpp"
#include "convert/EquirectToCubemap.hpp"
#include "layout/DiceLayout.hpp"
#include "Logger/Logger.hpp"

int main()
{
    bool force = false;
    bool resize = false;

    try {
        std::filesystem::path inputPath;

        std::cout << "Input image absolute path:\n> ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        inputPath = inputStr;

        if (!std::filesystem::exists(inputPath)) {
            Logger::error("Input file not found: " + inputPath.string());
            std::cin.get();
            return 1;
        }

        std::filesystem::path outputPath =
            inputPath.parent_path() /
            (inputPath.stem().string() + "_dice.png");

        int faceSize = 512;

        std::cout << "Face size (default 512):\n> ";
        std::string faceStr;
        std::getline(std::cin, faceStr);

        if (!faceStr.empty()) {
            faceSize = std::stoi(faceStr);
        }

        DiceLayoutPreset layoutPreset = DiceLayoutPreset::CrossHorizontal;

        std::cout <<
            "\nChoose dice layout:\n"
            "  [1] Cross (Horizontal)\n"
            "  [2] Cross (Vertical)\n"
            "  [3] Horizontal strip\n"
            "  [4] Vertical strip\n"
            "> ";

        std::string layoutChoice;
        std::getline(std::cin, layoutChoice);

        if (layoutChoice == "1") {
            layoutPreset = DiceLayoutPreset::CrossHorizontal;
        }
        else if (layoutChoice == "2") {
            layoutPreset = DiceLayoutPreset::CrossVertical;
        }
        else if (layoutChoice == "3") {
            layoutPreset = DiceLayoutPreset::Horizontal;
        }
        else if (layoutChoice == "4") {
            layoutPreset = DiceLayoutPreset::Vertical;
        }

        Logger::info("Loading: " + inputPath.string());

        Image src;
        if (!src.load(inputPath.string())) {
            Logger::error("Failed to load input image");
            std::cin.get();
            return 1;
        }

        float aspect = float(src.width) / float(src.height);

        if (std::abs(aspect - 2.0f) > 0.01f) {
            std::cout << "\n[FATAL] Input image is not equirectangular.\n\n";
            std::cout << "Image size : " << src.width << " x " << src.height << "\n";
            std::cout << "Aspect     : " << aspect << " : 1\n";
            std::cout << "Required   : 2.00 : 1\n\n";
            std::cout <<
                "Choose how to proceed:\n"
                "  [1] Abort (recommended)\n"
                "  [2] Force convert (distorted)\n"
                "  [3] Auto resize to 2:1 (LDR only)\n"
                "> ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "1" || choice.empty()) {
                Logger::info("Aborted by user");
                std::cin.get();
                return 0;
            }
            else if (choice == "2") {
                force = true;
                Logger::warn("Force mode enabled");
            }
            else if (choice == "3") {
                resize = true;
                Logger::warn("Resize mode enabled");
            }
            else {
                Logger::error("Invalid selection");
                std::cin.get();
                return 1;
            }
        }

        Logger::info("Converting to cubemap...");
        Cubemap cube = EquirectToCubemap::convert(src, faceSize, force, resize);
        Logger::info("Cubemap generated");

        Logger::info("Generating dice layout...");
        Image dice = DiceLayout::generate(cube, layoutPreset);
        Logger::info("Dice layout generated");

        Logger::info("Saving: " + outputPath.string());
        if (!dice.save(outputPath.string())) {
            Logger::error("Failed to save output image");
            std::cin.get();
            return 1;
        }

        Logger::info("Done!");
        std::cin.get();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "[FATAL] std::exception: " << e.what() << std::endl;
        std::cin.get();
        return 1;
    }
    catch (...) {
        std::cerr << "[FATAL] Unknown exception" << std::endl;
        std::cin.get();
        return 1;
    }
}