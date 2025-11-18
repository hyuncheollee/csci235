/*
Hyuncheol Lee
2025/11/15

this file is the source file for ChannelSwapFilter
*/

#include "ChannelSwapFilter.hpp"
#include "ImageFile.hpp"
#include "Pixel.hpp"

#include <string>
#include <vector>

// same part 0 blending formula used in the other filters
static int blendChannel(int oldValue, int newValue, double strength) {
    double keepOriginal = 1.0 - strength;
    return static_cast<int>(newValue * strength + oldValue * keepOriginal);
}

// helper to print the Channel enum nicely
static std::string channelToString(Channel c) {
    switch (c) {
        case RED:   return "RED";
        case GREEN: return "GREEN";
        case BLUE:  return "BLUE";
    }
    return "UNKNOWN";
}

/**
 * Constructs a ChannelSwapFilter with two channels
 * to swap and an optional strength.
 *
 * @param c1 The first channel as a Channel Enum
 * @param c2 The second channel as a Channel Enum
 * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
 */
ChannelSwapFilter::ChannelSwapFilter(Channel c1, Channel c2, double strength)
    : ImageFilter(strength), c1_(c1), c2_(c2) {
}

/**
 * Sets the channels to be swapped by the filter.
 *
 * @param c1 The first channel to swap as a Channel enum
 * @param c2 The second channel to swap as a Channel enum
 */
void ChannelSwapFilter::setSwapChannels(Channel c1, Channel c2) {
    c1_ = c1;
    c2_ = c2;
}

/**
 * Getter for swapped RGB channels
 *
 * @return A std::pair of Channels representing the swapped channels
 * @see Pairs in C++: https://www.geeksforgeeks.org/cpp/pair-in-cpp-stl/
 */
std::pair<Channel, Channel> ChannelSwapFilter::getSwapChannels() const {
    return std::make_pair(c1_, c2_);
}

/**
 * @brief Swaps the values of the filter's channels for every pixel,
 * then blends with the original pixel by strength.
 *
 * @param image A (non-const) reference to the ImageFile
 *
 * @post For each pixel:
 *  1. The selected channel values are swapped.
 *  2. The swapped version of the pixel is weighted by the filter strength,
 *     and the original pixel by (1.0 - strength).
 */
void ChannelSwapFilter::apply(ImageFile& image) const {
    double s = getStrength();

    // work on a copy of the pixel grid
    std::vector<std::vector<Pixel>> pixels = image.getPixels();

    int height = image.getHeight();
    int width  = image.getWidth();

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            Pixel& p = pixels[row][col];

            // store original and swapped values as arrays indexed by Channel
            int original[3] = { p.red, p.green, p.blue };
            int swapped[3]  = { p.red, p.green, p.blue };

            // swap the chosen channels in the swapped array
            int idx1 = static_cast<int>(c1_);
            int idx2 = static_cast<int>(c2_);
            int tmp  = swapped[idx1];
            swapped[idx1] = swapped[idx2];
            swapped[idx2] = tmp;

            // blend each channel between original and swapped
            int newR = blendChannel(original[RED],   swapped[RED],   s);
            int newG = blendChannel(original[GREEN], swapped[GREEN], s);
            int newB = blendChannel(original[BLUE],  swapped[BLUE],  s);

            p.red   = newR;
            p.green = newG;
            p.blue  = newB;
        }
    }

    // write changes back to the image
    image.setPixels(pixels);
}

/**
 * @brief Returns the filter name and swap details
 * @return A string like "ChannelSwapper [RED, BLUE]"
 */
std::string ChannelSwapFilter::name() const {
    return "ChannelSwapper [" +
           channelToString(c1_) + ", " +
           channelToString(c2_) + "]";
}
