/*
Hyuncheol Lee
2025/11/15

this file is the source file for InvertFilter
*/

#include "ImageFile.hpp" 
#include "InvertFilter.hpp"
#include "Pixel.hpp"

#include <vector>

// helper for the part 0 formula:
// new_channel = new_value * strength + old_value * (1 - strength)
static int blendChannel(int oldValue, int newValue, double strength) {
    double keepOriginal = 1.0 - strength;
    return static_cast<int>(newValue * strength + oldValue * keepOriginal);
}

/**
 * @brief Inverts the pixel colors of the given image, adjusting for the filter's strength
 *
 * @param image A (non-const) reference to the ImageFile object to which the filter will be applied.
 *
 * @post The image's pixel data is modified such that:
 * 1. The pixel colors are inverted using (255 - channel_value)
 * 2. The final pixel value is adjusted for the filter's strength by
 * averaging the inverted pixel color by the filter strength and
 * averaging the original pixel color by (1.0 - strength)
 *
 * @example See specs above for an example.
 */
void InvertFilter::apply(ImageFile& image) const {
    double s = getStrength();

    // work on a copy of the pixel grid
    std::vector<std::vector<Pixel>> pixels = image.getPixels();

    int height = image.getHeight();
    int width  = image.getWidth();

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            Pixel& p = pixels[row][col];

            int oldR = p.red;
            int oldG = p.green;
            int oldB = p.blue;

            // fully inverted color
            int fullR = 255 - oldR;
            int fullG = 255 - oldG;
            int fullB = 255 - oldB;

            // part 0 formula, channel by channel
            p.red   = blendChannel(oldR, fullR, s);
            p.green = blendChannel(oldG, fullG, s);
            p.blue  = blendChannel(oldB, fullB, s);
        }
    }

    // write changes back to the image
    image.setPixels(pixels);
}

/**
 * @brief Returns the name of the filter, that is "Invert Filter"
 * @return A string representing the name of the filter.
 */
std::string InvertFilter::name() const {
    return "Invert Filter";
}
