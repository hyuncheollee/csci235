#pragma once

#include "File.hpp"
#include "Pixel.hpp"
#include <string>
#include <vector>

class ImageFile : public File {

private:
    static bool isRectangular(const std::vector<std::vector<Pixel>>& array);
    const static int DEFAULT_WIDTH;
    const static int DEFAULT_HEIGHT;
    const static std::vector<std::vector<Pixel>> DEFAULT_PIXELS;
    std::vector<std::vector<Pixel>> pixels_;

public:
    /**
     * Constructs a new ImageFile object.
     *
     * The pixel data is stored in a 2D vector, where pixels[row][col] corresponds to
     * the pixel at the given row and column of the image.
     *
     * @pre Assume that the image ends with a valid image extension (i.e. you do not need to validate it).
     *
     * @param filename A const reference to a string representing the filename of the image.
     * @param pixels   A const reference to a 2D vector of Pixel objects representing the image's pixel data.
     *                 Defaults to a grid of 20(width) x 10(height) pixels initialized to black (0,0,0).
     * @param readable A boolean indicating whether the file is readable (defaults to true if omitted).
     * @param writable A boolean indicating whether the file is writable (defaults to true if omitted).
     *
     * @post
     * 1. The filename and permissions are initialized via the base File constructor.
     * 2. The pixel buffer is set to the provided vector, or initialized to the default size with all black pixels if...
     *  - The parameter is omitted (ie. as a default value).
     *  - Or the pixel array's rows are not all the same length.
     *
     * @note It IS allowed to set pixels to an empty 2D vector!
     */
    ImageFile(
        const std::string& filename,
        const std::vector<std::vector<Pixel>>& pixels = std::vector<std::vector<Pixel>>(DEFAULT_HEIGHT, std::vector<Pixel>(DEFAULT_WIDTH)),
        bool readable = true,
        bool writable = true);

    /**
     * Updates the pixel buffer of the image if given a valid pixel array; otherwise, returns false.
     *
     * @param pixels A const reference to a 2D vector of Pixel objects representing the new image data.
     * @returns True if the operation was successful, false otherwise.
     * @post
     * 1. If the new pixel array's rows are not all the same length, NO member is updated and false is returned.
     * 2. Otherwise, the pixels_ member variable is updated to match the provided 2D vector.
     *    and the last_modified_timestamp_ of the underlying File is updated to the current time
     *    specified by the Clock class
     *
     * @note It IS allowed to set pixels to an empty 2D vector!
     */
    bool setPixels(const std::vector<std::vector<Pixel>>& pixels);

    /**
     * Retrieves the current pixel buffer of the image.
     *
     * @return A 2D vector of Pixel objects, where pixels[row][col] corresponds to the pixel at
     *         the specified row and column.
     */
    std::vector<std::vector<Pixel>> getPixels() const;

    /**
     * Retrieves the height (number of rows) of the image.
     * @return An integer representing the total number of rows in the pixel buffer.
     */
    int getHeight() const;

    /**
     * Retrieves the width (number of columns) of the image.
     * @return An integer representing the total number of columns in the pixel buffer.
     */
    int getWidth() const;

    /**
     * Generates a string representation of the image file.
     *
     * @return A string containing the file's name, permissions, last modified timestamp,
     *         and image dimensions (width x height).
     */
    std::string toString() const;
};