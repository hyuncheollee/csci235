#pragma once

#include "File.hpp"
#include "ImageFile.hpp"
#include "TextFile.hpp"
#include "stb_image.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

namespace fs = std::filesystem;

class FileLoader {

private:
    const static int NUM_CHANNELS = 3;

    void checkExists(const fs::path& path) const;
    void checkExtensionIs(const fs::path& path, const std::vector<std::string>& supportedExtensions) const;

public:
    /**
     * Loads a text file from disk into a TextFile object.
     *
     * @param str_path_to_file A const reference to a STRING representing the path to the text file.
     * @return A TextFile object containing the file's name and contents.
     * @throws std::invalid_argument if:
     *  1. The file does not exist.
     *  2. The file extension is not ".txt".
     * @post
     * - All boolean File members are set to true
     * - The filename of the File is explicitly set to the name of the file only -- no directory
     *   information included.
     *   (e.g. "homework/my_file.txt" has a filename of "my_file.txt")
     *
     * @see Useful Links:
     * 1. C++ Exceptions: https://en.cppreference.com/w/cpp/header/stdexcept.html
     * 2. The <filesystem> path type: https://en.cppreference.com/w/cpp/filesystem/path/path.html
     * 3. Check if file Exists: https://en.cppreference.com/w/cpp/filesystem/exists.html
     * 4. Get the filename from a path
     */
    TextFile loadTextFile(const std::string& str_path_to_file);

    /**
     * Loads an image file from disk into an ImageFile object.
     *
     * Supported formats: PNG (.png) and JPEG (.jpg).
     *
     * @param str_path_to_file A const reference to a STRING representing the path to the image file.
     * @return An ImageFile object containing the file's name and pixel data buffer
     * @throws std::invalid_argument if:
     *  1. The file does not exist.
     *  2. The file extension is not ".png" or ".jpg".
     * @post
     * - All boolean File members are set to true
     * - All dynamic memory (that is, pointers) is released (so READ the documentation in stb file please)
     * - The filename of the File is explicitly set to the name of the file only -- no directory
     *   information included.
     *
     * @see stb_image.h Read the documentation section
     * - You will have to reshape the 1D array of RGB channel values
     *   into a 2D array of Pixel structs
     *
     * @example Suppose we have a width 2 by height 1 image,
     * with a white pixel on the left and black pixel on the right:
     *
     * The stb_image.h array would be:
     * `255 255 255 0 0 0`
     * Because:
     * 1. RGB(255,255,255) = white
     * 2. RGB(0,0,0) = black
     *
     * Importantly, notice that the incoming array would be the exact same given a 1x2 image
     * but your code MUST interpret that data differently to show a 1x2 image, not a 2x1.
     */
    ImageFile loadImageFile(const std::string& str_path_to_file);
};