/*
Hyuncheol Lee
2025/10/31

this file 
*/

#pragma once

class ImageFilter {
private:
    double strength_;        // A double representing the strength of the Image Filter

public: 
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
    ImageFilter(double initialStrength = 1.0);
    
    /**
     * Sets the strength of the filter.
     *
     * @param strength A double representing the new filter strength,
     * clamped between 0.0 and 1.0
     */
    void setStrength(double strength);

    /**
     * Getter for the strength_ member
     */
    double getStrength() const;

    /**
     * @brief Applies the filter to the given image.
     * @param image A (non-const) reference to the ImageFile object to which the filter will be applied.
     *
     * @post The parameter image's pixel data is modified to reflect the applied filter effect.
     * @note The filter modifies the image directly -- nothing is returned.
     * @note To prevent confusion: NONE of the filter's members should be modified by this
     * (this is one of the few times where we tell you this function is const).
     * @note Pure virtual -- will be implemented later by derived classes
     */
    apply

    /**
     * @brief Returns the name of the filter as a string
     * @return A string containg the name of the filter
     *
     * @note Pure virtual -- will be implemented later by derived classes
     */
    name
}; 
