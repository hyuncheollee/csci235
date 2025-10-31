#include "FileLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    FileLoader loader;
    ImageFile f = loader.loadImageFile("sample_img.png");
    // TextFile f = loader.loadTextFile("sample_text.txt");
    std::cout << f.toString() << std::endl;
    return 0;
}