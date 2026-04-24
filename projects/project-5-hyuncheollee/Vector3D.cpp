#include "Vector3D.hpp"
#include <cmath>

Vector3D::Vector3D() : x_(0), y_(0), z_(0) {}

Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}

double Vector3D::getX() const { return x_; }
double Vector3D::getY() const { return y_; }
double Vector3D::getZ() const { return z_; }

void Vector3D::setX(double x) { x_ = x; }
void Vector3D::setY(double y) { y_ = y; }
void Vector3D::setZ(double z) { z_ = z; }

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x_ * scalar, y_ * scalar, z_ * scalar);
}

bool Vector3D::operator==(const Vector3D& other) const {
    const double epsilon = 0.001;
    return std::abs(x_ - other.x_) < epsilon &&
           std::abs(y_ - other.y_) < epsilon &&
           std::abs(z_ - other.z_) < epsilon;
}