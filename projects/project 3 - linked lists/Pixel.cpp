#include "Pixel.hpp"

bool Pixel::operator==(const Pixel& rhs) const
{
    return red == rhs.red && green == rhs.green && blue == rhs.blue;
}

bool Pixel::operator!=(const Pixel& rhs) const
{
    return !(*this == rhs);
}

std::string Pixel::toString() const
{
    std::stringstream ss;
    ss << "[ " << red << ", " << green << ", " << blue << " ]";
    return ss.str();
}