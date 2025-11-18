/*
Hyuncheol Lee
2025/10/31

this file is the source file for ImageFilter
*/

#include "ImageFilter.hpp"

#include <string>

/**
 * Constructs an ImageFilter with a given initial strength.
 *
 * @param initialStrength A double representing the initial filter strength,
 * clamped between 0.0 and 1.0. Default value of 1.0
 *
 * @note Clamped just means that given a range of values [0,1] and value:
 * If the value is...
 * 1. Between [0,1] use the actual value
 * 2. Less than 0 use 0.0
 * 3. Greater than 1, use 1.0
 */
ImageFilter::ImageFilter(double initialStrength) {
    // value is smaller than 0.0
    if (initialStrength < 0.0) {
        strength_ = 0.0;
    }

    // value is larger than 1.0
    else if (initialStrength > 1.0) {
        strength_ = 1.0;
    }

    // value is between 0.0 and 1.0
    else {
        strength_ = initialStrength;
    }
}

/**
 * Sets the strength of the filter.
 *
 * @param strength A double representing the new filter strength,
 * clamped between 0.0 and 1.0
 */
void ImageFilter::setStrength(double strength) {
    // value is smaller than 0.0
    if (strength < 0.0) {
        strength_ = 0.0;
    }

    // value is larger than 1.0
    else if (strength > 1.0) {
        strength_ = 1.0;
    }

    // between 0.0 and 1.0
    else {
        strength_ = strength;
    }
}

/**
 * Getter for the strength_ member
 */
double ImageFilter::getStrength() const {
    return strength_;
}
