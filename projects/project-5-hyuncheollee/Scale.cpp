#include "Scale.hpp"

Scale::Scale(double factor) : factor_(factor) {}

Vector3D Scale::apply(const Vector3D& point) const {
    return point * factor_; // Uses the operator* we added to Vector3D
}

std::string Scale::getType() const {
    return "SCALE";
}