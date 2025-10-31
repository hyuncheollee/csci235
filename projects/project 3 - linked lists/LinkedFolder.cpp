/*
Hyuncheol Lee
2025/10/17

this file deals with linked folders
*/

#include "LinkedFolder.hpp"

/**
 * @brief Finds the index of a file with the given filename.
 * @param filename The name of the file to search for.
 *
 * @return The zero-based index of the file if found;
 * otherwise, returns the size of the internal LinkedList
 * (i.e. an index which is out of bounds of the actual LinkedList).
 */
size_t LinkedFolder::indexOf(const std::string& filename) const {
    for (size_t i = 0; i < files_.size(); ++i) {
        if (files_.at(i).getFilename() == filename) {
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
size_t LinkedFolder::getFileCount() const {
    return files_.size();
}

/**
 * @brief Searches for a file by its name.
 * @param filename The name of the file to find, as a const reference to a string
 *
 * @throw std::runtime_error If the file is not found in the folder.
 * @return The file whose filename matches exactly, within the folder's files.
 */
File LinkedFolder::findFile(const std::string& filename) const {
    size_t idx = indexOf(filename);

    // file not found in folder
    if (idx >= files_.size()) {
        throw std::runtime_error("file not found in folder: " + filename);
    }

    return files_.at(idx);
}

/**
 * @brief Adds a new file to the folder.
 *
 * The file will not be added if a file with the same name already exists.
 *
 * @param file The File object to be added as a const reference.
 * @return True if the file was successfully added, false otherwise.
 */
bool LinkedFolder::addFile(const File& file) {
    if (indexOf(file.getFilename()) < files_.size()) {
        return false;
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
bool LinkedFolder::removeFile(const std::string& filename) {
    size_t idx = indexOf(filename);

    // cannot find file
    if (idx >= files_.size()) {
        return false;      
    }

    // erase file
    files_.erase(idx);

    return true;
}

/**
 * @brief Access the underlying files linked list
 * @return A LinkedList of File objects representing
 * the files in the LinkedFolder
 */
LinkedList<File> LinkedFolder::getFiles() const {
    return files_;
}
