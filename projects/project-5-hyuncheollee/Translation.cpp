#include "Translation.hpp"

Translation::Translation(double tx, double ty, double tz) : offset_(tx, ty, tz) {}

Vector3D Translation::apply(const Vector3D& point) const {
    return point + offset_; // Uses the operator+ we added to Vector3D
}

std::string Translation::getType() const {
    return "TRANSLATE";
}