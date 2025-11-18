/*
Hyuncheol Lee
2025/11/15

this file is the source file for ColorFilter
*/

#include "ColorFilter.hpp"
#include "ImageFile.hpp"
#include "Pixel.hpp"

#include <string>
#include <vector>

// helper for the part 0 formula:
// new_channel = new_value * strength + old_value * (1 - strength)
static int blendChannel(int oldValue, int newValue, double strength) {
    double keepOriginal = 1.0 - strength;
    return static_cast<int>(newValue * strength + oldValue * keepOriginal);
}

// clamp a single channel to [0, 255]
int ColorFilter::clampChannel(int value) {
    if (value < 0) {
        return 0;
    }
    if (value > 255) {
        return 255;
    }
    return value;
}

/**
 * Constructs a ColorFilter with a given overlay color and strength.
 *
 * @param red The red channel value of the overlay color
 * @param green The green channel value of the overlay color
 * @param blue The blue channel value of the overlay color
 * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
 */
ColorFilter::ColorFilter(int red, int green, int blue, double strength)
    : ImageFilter(strength) {
    setColor(red, green, blue);
}

/**
 * Sets the overlay color of the filter.
 *
 * @param r the new red channel value, clamped to [0,255]
 * @param g the new green channel value, clamped to [0,255]
 * @param b the new blue channel value, clamped to [0,255]
 */
void ColorFilter::setColor(int r, int g, int b) {
    color_.red   = clampChannel(r);
    color_.green = clampChannel(g);
    color_.blue  = clampChannel(b);
}

/**
 * Gets the overlay color of the filter.
 *
 * @return The filter's red, green & blue color
 * as a Pixel object
 */
Pixel ColorFilter::getColor() const {
    return color_;
}

/**
 * @brief Applies the color overlay to each pixel in the image,
 * blended according to strength
 * @param image A (non-const) reference to the ImageFile
 *
 * @post The image's pixel data is modified such that:
 * The final pixel value is adjusted for the filter's strength by
 * averaging the ColorFilter's color by the filter strength and
 * averaging the original pixel color by (1.0 - strength)
 */
void ColorFilter::apply(ImageFile& image) const {
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

            int overlayR = color_.red;
            int overlayG = color_.green;
            int overlayB = color_.blue;

            // blend overlay color with original pixel, channel by channel
            p.red   = blendChannel(oldR, overlayR, s);
            p.green = blendChannel(oldG, overlayG, s);
            p.blue  = blendChannel(oldB, overlayB, s);
        }
    }

    // write changes back to the image
    image.setPixels(pixels);
}

/**
 * @brief Returns the name of the filter
 *
 * @return A string of the form:
 *
 * `Color Filter [<red_channel>, <green_channel>, <blue_channel>]`
 *
 * @example If we have a red filter, this would return:
 * `Color Filter [255,0,0]`
 */
std::string ColorFilter::name() const {
    // formated Color Filter [r,g,b]
    return "Color Filter [" +
           std::to_string(color_.red) + "," +
           std::to_string(color_.green) + "," +
           std::to_string(color_.blue) + "]";
}
