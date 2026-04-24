#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Vector3D.hpp"
#include <string>

class Transformation {
public:
    virtual ~Transformation() = default;
    virtual Vector3D apply(const Vector3D& point) const = 0;
    virtual std::string getType() const = 0; // Required for filtering
};

#endif