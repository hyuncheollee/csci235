/*
Hyuncheol Lee
2025/10/08

this file loads files from your disk
*/

#include "FileLoader.hpp"
#include "ImageFile.hpp"
#include "TextFile.hpp"
#include "stb_image.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

/**
 * Loads a text file from disk into a TextFile object.
 *
 * @param str_path_to_file A const reference to a STRING representing the path to the text file.
 * @return A TextFileobject containing the file's name and contents.
 * @throws std::invalid_argument if:
 *  1. The file does not exist.
 *  2. The file extension is not ".txt".
 * @post
 * - All boolean File members are set to true
 * - The File filename is explicitly set to the name of the file only -- no directory
 *   information included.
 *   (e.g. "homework/my_file.txt" has a filename of "my_file.txt")
 * - The TextFile contents is set to the text content of the specified file
 *
 * @see Useful Links:
 * 1. C++ Exceptions: https://en.cppreference.com/w/cpp/header/stdexcept.html
 * 2. The std::filesystem::path (from <filesystem> header) type: https://en.cppreference.com/w/cpp/filesystem/path.html
 *    - Contains how to get the extension & filename from the file system path
 *    - How to create a path object: https://stackoverflow.com/questions/43114174/convert-a-string-to-std-filesystem-path
 * 3. Check if file Exists: https://en.cppreference.com/w/cpp/filesystem/exists.html
 * 4. Input File Streams (refresher from 135): https://www.w3schools.com/cpp/ref_fstream_ifstream.asp
*/
TextFile FileLoader::loadTextFile(const std::string& str_path_to_file) {
    fs::path file_path(str_path_to_file);

    // checks if file exists
    if (!fs::exists(file_path)) {
        throw std::invalid_argument("The file does not exist.");
    }

    // checks file extension
    if (file_path.extension() != ".txt") {
        throw std::invalid_argument("The file extension is not '.txt'.");
    }
    
    // open the file
    std::ifstream file(str_path_to_file);

    // checks to see if we can open the file
    if (!file.is_open()) {
        throw std::invalid_argument("Failed to open the file.");
    }

    // loads the file's content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    /**
     * created a TextFile object
     * name of file is explicitly set to the name of the file and does not include dir info
     * the TextFile contents are set to the text content of the specified file
     * bools set to true
    **/
     return TextFile(file_path.filename().string(), contents, true, true);
}

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
*/
ImageFile FileLoader::loadImageFile(const std::string& str_path_to_file) {
    fs::path file_path(str_path_to_file);

    // checks if file exists
    if (!fs::exists(file_path)) {
        throw std::invalid_argument("The file does not exist: " + str_path_to_file);
    }

    // checks file extension
    std::string ext = file_path.extension().string();
    if (ext != ".png" && ext != ".jpg") {
        throw std::invalid_argument("Unsupported file extension: " + ext);
    }

    int width, height, channels;
    unsigned char* data = stbi_load(str_path_to_file.c_str(), &width, &height, &channels, 3); // force 3 channels -- rbg
    if (!data) {
        throw std::runtime_error("Failed to load image: " + str_path_to_file);
    }

    // 1d data -> 2d data vector
    std::vector<std::vector<Pixel>> pixels(height, std::vector<Pixel>(width));
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int index = (row * width + col) * 3; // 3 channels per pixel
            pixels[row][col] = Pixel{
                data[index],      // red
                data[index + 1],  // green
                data[index + 2]   // blue
            };
        }
    }

    // free the raw data
    stbi_image_free(data);

    // create and return ImageFile
    return ImageFile(file_path.filename().string(), pixels, true, true);
}
