#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>

class Vector3D {
public:
    // Constructors
    Vector3D();
    Vector3D(double x, double y, double z);

    // Accessors
    double getX() const;
    double getY() const;
    double getZ() const;
    
    // Mutators (Optional but good practice)
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    /**
     * @brief Adds two vectors together.
     * @param other The vector to add.
     * @return A new Vector3D representing the sum.
     */
    Vector3D operator+(const Vector3D& other) const;

    /**
     * @brief Multiplies the vector by a scalar.
     * @param scalar The factor to scale by.
     * @return A new Vector3D representing the scaled vector.
     */
    Vector3D operator*(double scalar) const;
    
    /**
     * @brief Checks equality with epsilon tolerance.
     */
    bool operator==(const Vector3D& other) const;

private:
    double x_, y_, z_;
};

#endif