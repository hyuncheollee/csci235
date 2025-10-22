/*
Hyuncheol Lee
2025/10/17

this file deals with files in folders
*/

#include "VectorFolder.hpp"

/**
 * @brief Default constructor.
 *
 * Initializes an empty VectorFolder with no files.
 */
VectorFolder::VectorFolder() : files_() {
    // files_ is automatically initialized as an empty vector
}

/**
 * @brief Finds the index of a file with the given filename.
 * @param filename The name of the file to search for.
 *
 * @return The zero-based index of the file if found;
 * otherwise, returns the size of the internal vector
 * (i.e. an index which is out of bounds of the actual vector).
 */
size_t VectorFolder::indexOf(const std::string& filename) const {
    for (size_t i = 0; i < files_.size(); ++i) {
        if (files_[i].getFilename() == filename) { 
            return i;
        }
    }

    // not found
    return files_.size();
}

/**
 * @brief Gets the total number of files currently in the folder.
 * @return The count of files as a size_t.
 */
size_t VectorFolder::getFileCount() const {
    return files_.size();
}

/**
 * @brief Searches for a file by its name.
 * @param filename The name of the file to find, as a const reference to a string
 *
 * @throw std::runtime_error If the file is not found in the folder.
 * @return The file whose filename matches exactly, within the folder's files.
 */
File VectorFolder::findFile(const std::string& filename) const {
    size_t idx = indexOf(filename);

    if (idx >= files_.size()) {
        throw std::runtime_error("file not found in folder: " + filename);
    }

    return files_[idx];
}

/**
 * @brief Adds a new file to the folder.
 *
 * The file will not be added if a file with the same name already exists.
 *
 * @param file The File object to be added as a const reference.
 * @return True if the file was successfully added, false otherwise.
 */
bool VectorFolder::addFile(const File& file) {
    // check if file already exists
    if (indexOf(file.getFilename()) < files_.size()) {
        return false;       // file exists, do not add
    }

    files_.push_back(file);

    return true;
}

/**
 * @brief Removes a file from the folder by its name.
 *
 * The file will not be removed if a file with the same name does NOT exist in the collection.
 *
 * @param filename The name of the file to remove, as a const. ref. to a string
 * @return True if the file was found and removed, false otherwise.
 */
bool VectorFolder::removeFile(const std::string& filename) {
    size_t idx = indexOf(filename);

    // file not found
    if (idx >= files_.size()) {
        return false;       
    }

    files_.erase(files_.begin() + idx);

    return true;
}

/**
 * @brief Access the underlying files vector
 * @return A vector of File objects representing the files in the VectorFolder
 */
std::vector<File> VectorFolder::getFiles() const {
    return files_;
}
