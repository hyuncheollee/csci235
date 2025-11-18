/*
Hyuncheol Lee
2025/11/15

this file is the source file for InvertFilter
*/

#pragma once

#include "ImageFilter.hpp"

class InvertFilter : public ImageFilter {
public:
    // constructors
    /**
     * Constructs an ImageFilter at full strength
     * @post Sets the underlying strength to 1.0
     */
    InvertFilter() : ImageFilter(1.0) {}

    /**
     * Constructs an ImageFilter at full strength
     *
     * @param initialStrength The initial filter strength, as a double
     * @post Clamps the given strength to [0.0, 1.0], if necessary
     * and sets the underlying strength of the ImageFilter
     */
    InvertFilter(double initialStrength) : ImageFilter(initialStrength) {}

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
    void apply(ImageFile& image) const override;
    
    /**
     * @brief Returns the name of the filter, that is "Invert Filter"
     * @return A string representing the name of the filter.
     */
    std::string name() const override;
};
