#include "FileLoader.hpp"

const std::string FileLoader::SAVE_IMAGE_AS_EXTENSION = ".jpg";

void FileLoader::checkExists(const fs::path& path) const
{
    if (!fs::exists(path)) {
        throw std::invalid_argument("File does not exist: " + path.string());
    }
}

void FileLoader::checkNotExists(const fs::path& path) const
{
    if (fs::exists(path)) {
        throw std::invalid_argument("File already exists: " + path.string());
    }
}

void FileLoader::checkDirectory(const fs::path& path) const
{
    if (!fs::is_directory(path)) {
        throw std::invalid_argument("Not a valid directory: " + path.string());
    }
}

void FileLoader::checkExtensionIs(const fs::path& path, const std::vector<std::string>& supportedExtensions) const
{
    std::string ext = path.extension().string();
    auto found_itr = std::find(supportedExtensions.begin(), supportedExtensions.end(), ext);
    if (found_itr == supportedExtensions.end()) {
        throw std::invalid_argument("Unsupported extension: " + ext);
    }
}

TextFile FileLoader::loadTextFile(const std::string& path_to_file_str) const
{
    fs::path filepath = path_to_file_str;

    checkExists(filepath);
    checkExtensionIs(filepath, { ".txt" });

    std::ifstream fin(filepath);
    std::stringstream strStream;
    strStream << fin.rdbuf();
    std::string content = strStream.str();

    return TextFile(
        filepath.filename().string(),
        content);
}

ImageFile FileLoader::loadImageFile(const std::string& path_to_file_str) const
{
    fs::path filepath = path_to_file_str;

    checkExists(filepath);
    checkExtensionIs(filepath, { ".png", ".jpg" });

    int width, height, channels_in_file;
    unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &channels_in_file, NUM_CHANNELS);
    std::vector<std::vector<Pixel>> buffer(height, std::vector<Pixel>(width));

    int row = 0;
    int col = 0;
    for (int counter = 0; counter < width * height * 3; counter += 3) {
        Pixel p = {
            data[counter],
            data[counter + 1],
            data[counter + 2],
        };

        buffer[row][col] = p;
        col++;

        if (col == width) {
            row++;
            col = 0;
        }
    }

    stbi_image_free(data);

    return ImageFile(
        filepath.filename().string(),
        buffer);
}

std::unique_ptr<unsigned char[]> FileLoader::toArray(const std::vector<std::vector<Pixel>>& pixels) const
{
    if (pixels.empty() || pixels[0].empty()) {
        return std::make_unique<unsigned char[]>(0);
    }

    int height = pixels.size();
    int width = pixels[0].size();

    // Allocate memory for the 1D array (width * height * number_of_channels)
    auto data = std::make_unique<unsigned char[]>(width * height * NUM_CHANNELS);

    int index = 0;
    for (size_t i = 0; i < pixels.size(); ++i) {
        for (size_t j = 0; j < pixels[i].size(); ++j) {
            data[index] = static_cast<unsigned char>(pixels[i][j].red);
            data[index + 1] = static_cast<unsigned char>(pixels[i][j].green);
            data[index + 2] = static_cast<unsigned char>(pixels[i][j].blue);
            index += 3;
        }
    }
    return data;
}

void FileLoader::saveImageFile(const ImageFile& image, const std::string& file_stem, const std::string& directory) const
{
    fs::path fs_target_directory = directory;
    checkExists(fs_target_directory);
    checkDirectory(fs_target_directory);

    fs::path fs_filename = file_stem + SAVE_IMAGE_AS_EXTENSION;
    fs::path fs_full_target_path = fs_target_directory / fs_filename;
    checkNotExists(fs_full_target_path);

    std::unique_ptr<unsigned char[]> data = toArray(image.getPixels());

    stbi_write_jpg(
        fs_full_target_path.string().c_str(),
        image.getWidth(),
        image.getHeight(),
        NUM_CHANNELS,
        data.get(),
        JPEG_SAVE_QUALITY);
}
