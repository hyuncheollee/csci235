/**
 * @file Scale.hpp
 * @brief Concrete class for resizing points relative to origin.
 */

#ifndef SCALE_HPP
#define SCALE_HPP

#include "Transformation.hpp"
#include <string>

class Scale : public Transformation {
public:
    /**
     * @param factor: The uniform scaling factor.
     * @post: Initializes the scale factor.
     */
    Scale(double factor);

    Vector3D apply(const Vector3D& point) const override;
    
    std::string getType() const override;

private:
    double factor_;
};

#endif