/*
Hyuncheol Lee
2025/10/08

this file loads files from your disk
*/

#pragma once

#include "ImageFile.hpp"
#include "TextFile.hpp"
#include <string>

class FileLoader {
public:
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
    static TextFile loadTextFile(const std::string& str_path_to_file);

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
    static ImageFile loadImageFile(const std::string& str_path_to_file);
};
