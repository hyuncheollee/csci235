/*
Hyuncheol Lee
2025/10/17

this file deals with linked folders
*/

#pragma once

#include "File.hpp"
#include "LinkedList.hpp"
#include <string>
#include <stdexcept>

class LinkedFolder {
private:
    LinkedList<File> files_;  // underlying linked list of files

    /**
     * @brief Finds the index of a file with the given filename.
     * @param filename The name of the file to search for.
     * @return The zero-based index of the file if found; otherwise, returns files_.size()
     */
    size_t indexOf(const std::string& filename) const;

public:    
    LinkedFolder() = default;
    /**
     * @brief Gets the total number of files in the folder.
     * @return The count of files as a size_t.
     */
    size_t getFileCount() const;

    /**
     * @brief Searches for a file by its name.
     * @param filename The name of the file to find.
     * @throw std::runtime_error if the file is not found.
     * @return The file whose filename matches exactly.
     */
    File findFile(const std::string& filename) const;

    /**
     * @brief Adds a new file to the folder.
     * @param file The File object to add.
     * @return True if added, false if a file with the same name exists.
     */
    bool addFile(const File& file);

    /**
     * @brief Removes a file from the folder by name.
     * @param filename The name of the file to remove.
     * @return True if removed, false if not found.
     */
    bool removeFile(const std::string& filename);

    /**
     * @brief Access the underlying files linked list.
     * @return A copy of the LinkedList<File> representing all files.
     */
    LinkedList<File> getFiles() const;
};
