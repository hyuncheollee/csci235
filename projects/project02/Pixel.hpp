#pragma once

#include <sstream>
#include <string>

/**
 * Represents a single pixel in an image using RGB color values.
 *
 * Each pixel is defined by three integer components:
 *  - red   : intensity of the red channel (0–255).
 *  - green : intensity of the green channel (0–255).
 *  - blue  : intensity of the blue channel (0–255).
 *
 * By default, a Pixel is initialized to black (0, 0, 0).
 */
struct Pixel {
    int red { 0 };
    int green { 0 };
    int blue { 0 };

    /**
     * Compares this Pixel object to another Pixel object for equality.
     *
     * Two pixels are considered equal if all their corresponding color
     * component values (e.g., red, green, blue) are the same.
     *
     * @param rhs The other Pixel object to compare against.
     * @return true if the pixels are equal, false otherwise.
     * @example
     * Pixel p1 = new Pixel(255, 0, 0);
     * Pixel p2 = new Pixel(255, 0, 0);
     *
     * boolean areEqual = (p1 == p2); // returns true
     */
    bool operator==(const Pixel& rhs) const;

    /**
     * Compares this Pixel object to another Pixel object for inequality.
     *
     * Two pixels are considered unequal if at least one of their
     * corresponding color component values differs. This is effectively
     * the logical negation of the equality operator.
     *
     * @param rhs The other Pixel object to compare against.
     * @return true if the pixels are not equal, false otherwise.
     * @example
     * Pixel p1 = new Pixel(255, 0, 0);
     * Pixel p3 = new Pixel(0, 0, 255);
     *
     * boolean areDifferent = (p1 != p3); // returns true
     */
    bool operator!=(const Pixel& rhs) const;

    /**
     * Converts the Pixel object's color values into a formatted string representation
     * of the form "[<red>, <green>, <blue>]"
     *
     * @return A string representing the pixel's color values.
     */
    std::string toString() const;
};
