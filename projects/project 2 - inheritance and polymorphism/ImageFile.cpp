/*
Hyuncheol Lee
2025/10/05

this file deals with the given file's image data
*/

#include "ImageFile.hpp"
#include "File.hpp"

// parametized constructor
/**
 * Constructs a new ImageFile object.
 *
 * The pixel data is stored in a 2D vector, where pixels[row][col] corresponds to
 * the pixel at the given row and column of the image.
 *
 * @pre Assume that the image ends with a valid image extension (i.e. you do not need to validate it).
 *
 * @param filename A const reference to a string representing the filename of the image.
 * @param pixels A const reference to a 2D vector of Pixel objects representing the image's pixel data.
 * Defaults to a grid of 20(width) x 10(height) pixels initialized to black (0,0,0).
 * @param readable A boolean indicating whether the file is readable (defaults to true if omitted).
 * @param writable A boolean indicating whether the file is writable (defaults to true if omitted).
 *
 * @post
 * 1. The filename and permissions are initialized via the base File constructor.
 * 2. The pixel buffer is set to the provided vector, or initialized to the default size with all black pixels if...
 * - The parameter is omitted (ie. as a default value).
 * - Or the pixel array's rows are not all the same length.
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
 */
ImageFile::ImageFile(const std::string& filename, const std::vector<std::vector<Pixel>>& pixels, bool readable, bool writable) : File(filename, readable, writable) {       
    if (!pixels.empty()) {                                                                          
        size_t expected_width = pixels[0].size();                                                   // checking first row's length
        for (const auto& row : pixels) {                
            if (row.size() != expected_width) {                                                     // going to compare length of each row with the length of first row
                pixels_ = std::vector<std::vector<Pixel>>(10, std::vector<Pixel>(20, {0,0,0}));     // found a row with a different length
                return;                                                                             // no need to continue, exit constructor
            }
        }    
    }
    pixels_ = pixels;                                                                               // vector is empty or all rows in vector are the same length, use provided vector       
}

// getter
/**
 * Retrieves the current pixel buffer of the image.
 *
 * @return A 2D vector of Pixel objects, where pixels[row][col] corresponds to the pixel at
 * the specified row and column.
*/
std::vector<std::vector<Pixel>> ImageFile::getPixels() const {
    return pixels_;
}
/**
 * Retrieves the height (number of rows) of the image.
 * @return An integer representing the total number of rows in the pixel buffer.
*/
int ImageFile::getHeight() const {
    return pixels_.size();
}

/**
 * Retrieves the width (number of columns) of the image.
 * @return An integer representing the total number of columns in the pixel buffer.
 */
int ImageFile::getWidth() const {
    return pixels_.empty() ? 0 : pixels_[0].size();
}

// setter
/**
 * Updates the pixel buffer of the image if given a valid pixel array; otherwise, returns false.
 *
 * @param pixels A const reference to a 2D vector of Pixel objects representing the new image data.
 * @returns True if the operation was successful, false otherwise.
 * @post
 * 1. If the new pixel array's rows are not all the same length, NO member is updated and false is returned.
 * 2. Otherwise, the pixels_ member variable is updated to match the provided 2D vector.
 * and the last_modified_timestamp_ of the underlying File is updated to the current time
 * specified by the Clock class
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
*/
bool ImageFile::setPixels(const std::vector<std::vector<Pixel>>& pixels) {
    // if the vector is empty
    if (pixels.empty()) {
        pixels_ = pixels;
        File::updateLastModified();
        return true;
    }

    // let's check if all the rows are the same length
    size_t expected_width = pixels[0].size();
    for (const auto& row : pixels) {
        if (row.size() != expected_width) {
            return false;       // not the same length, do not update
        }
    }

    // couldn't find anything wrong
    pixels_ = pixels;
    File::updateLastModified();
    return true;
}

// tester
/**
 * Generates a string representation of the image file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 * and image dimensions (width x height).
*/
std::string ImageFile::toString() const {
    std::stringstream ss;

    // Call the base class toString()
    ss << File::toString();

    // Display image metadata
    ss << "Resolution: " << getWidth() << "x" << getHeight() << std::endl;

    // Display pixel buffer
    ss << "[" << std::endl;

    for (int i = 0; i < getHeight(); i++) {
        ss << "\t";

        for (int j = 0; j < getWidth(); j++) {
        ss << pixels_[i][j].toString() << " ";
        }
        ss << std::endl;
    }

    ss << "]";
    return ss.str();
}
