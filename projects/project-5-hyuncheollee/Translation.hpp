/**
 * @file Translation.hpp
 * @brief Concrete class for moving points in space.
 */

#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include "Transformation.hpp"
#include <string>

class Translation : public Transformation {
public:
    /**
     * @param tx, ty, tz: The displacement values.
     * @post: Initializes the internal offset vector.
     */
    Translation(double tx, double ty, double tz);

    Vector3D apply(const Vector3D& point) const override;
    
    std::string getType() const override;

private:
    Vector3D offset_;
};

#endif