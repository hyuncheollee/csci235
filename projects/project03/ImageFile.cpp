#include "ImageFile.hpp"

const int ImageFile::DEFAULT_WIDTH = 20;
const int ImageFile::DEFAULT_HEIGHT = 10;
const std::vector<std::vector<Pixel>> ImageFile::DEFAULT_PIXELS = std::vector<std::vector<Pixel>>(DEFAULT_HEIGHT, std::vector<Pixel>(DEFAULT_WIDTH));

ImageFile::ImageFile(
    const std::string& filename,
    const std::vector<std::vector<Pixel>>& pixels,
    bool readable,
    bool writable)
    : File(filename, readable, writable)
    , pixels_(isRectangular(pixels) ? pixels : DEFAULT_PIXELS)
{
}

bool ImageFile::isRectangular(const std::vector<std::vector<Pixel>>& array)
{
    if (array.empty()) {
        return true;
    }

    for (size_t i = 1; i < array.size(); i++) {
        if (array[i].size() != array[i - 1].size()) {
            return false;
        }
    }
    return true;
}

bool ImageFile::setPixels(const std::vector<std::vector<Pixel>>& pixels)
{
    if (!isRectangular(pixels)) {
        return false;
    }

    pixels_ = pixels;
    File::updateLastModified();
    return true;
}

std::vector<std::vector<Pixel>> ImageFile::getPixels() const
{
    return pixels_;
}

int ImageFile::getHeight() const
{
    if (pixels_.empty()) {
        return 0;
    }
    return pixels_.size();
}

int ImageFile::getWidth() const
{
    if (pixels_.empty()) {
        return 0;
    }
    return pixels_[0].size();
}

std::string ImageFile::toString() const
{
    std::stringstream ss;
    ss << File::toString();
    ss << "Resolution: " << getWidth() << "x" << getHeight() << std::endl;
    ss << "[" << std::endl;

    for (int i = 0; i < getHeight(); i++) {
        ss << "\t";
        for (int j = 0; j < getWidth(); j++) {
            ss << pixels_[i][j].toString() << " ";
        }
        ss << std::endl;
    }
    ss << "]";
    return ss.str();
}