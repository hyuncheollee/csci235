#include "ImageFile.hpp"

const int ImageFile::DEFAULT_WIDTH = 20;
const int ImageFile::DEFAULT_HEIGHT = 10;

ImageFile::ImageFile(
    const std::string& filename,
    const std::vector<std::vector<Pixel>>& pixels,
    bool readable,
    bool writable)
    : File(filename, readable, writable)
    , pixels_(pixels)
{
}

void ImageFile::setPixels(const std::vector<std::vector<Pixel>>& pixels)
{
    pixels_ = pixels;
    File::updateLastModified();
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