/*
Hyuncheol Lee
2025/09/20

this file implements things declared in File.hpp
*/

#include <chrono>
#include <sstream>
#include <string>
#include "File.hpp"
#include "FileUtils.hpp"

// constructors
/**
 * Constructs a new File object.
 *
 * @post
 * Sets the File's filename_ to "New_Text_Document.txt"
 * Sets all boolean members to true.
 * `last_modified_timestamp_` is set to the current system time.
*/
File::File() {                                                                              // default constructor
    filename_ = "New_Text_Document.txt";
    readable_ = true;
    writable_ = true;
    last_modified_timestamp_ = cr::system_clock::now();
}

/**
 * Constructs a new File object.
 *
 * @param filename A const reference to a string for the initial filename
 * @param isReadable A const reference to a boolean for the readable permission
 * @param isWritable A const reference to a boolean for the writable permission
 *
 * @post
 * All booleans should have a default value of true (ie. use true if they are omitted).
 *
 * Sets the File's filename_ such that:
 * 1. If the parameter contains spaces or has no characters at all, the default filename is used
 * 2. If the parameter has no extension (no `period` characters whatsoever), .txt is appended to the filename & used
 * 3. If the parameter has an empty extension (a `period` characters followed by no characters), txt is appended to the filename & used
 * 4. Otherwise, the parameter filename is used as is
 * Note: A filename like `.env` or `.log` IS allowed (ie. filenames containing only the extension)!
 * 
 * `last_modified_timestamp_` is set to the current system time.
*/
File::File(const std::string& filename, const bool& isReadable, const bool& isWritable) {   // parametized constructor
    if (filename.empty() || FileUtils::hasWhitespaces(filename)) {      // checks if filename is empty or contains whitespaces
        filename_ = "New_Text_Document.txt";
        readable_ = isReadable;
        writable_ = isWritable;
        last_modified_timestamp_ = cr::system_clock::now();
        return;
    }

    
    std::string extension = FileUtils::findFileExtension(filename);     // let's check if there's an extension

    if (extension == "") {                                              // if there's no extension, append .txt
        filename_ = filename + ".txt";
    }

    else if (extension == ".") {                                        // if empty extension, append txt
        filename_ = filename + "txt";
    }

    else {                                                              // can't find anything wrong
    filename_ = filename;
    }

    readable_ = isReadable;
    writable_ = isWritable;
    last_modified_timestamp_ = cr::system_clock::now();
}

// getters
/**
 * Retrieves the current readable permission as a boolean.
 * @return The value stored in `readable_`
*/
bool File::isReadable() const {
    return readable_;
}   

/**
 * Retrieves the current writable permission as a boolean.
 * @return The value stored in `writable_`
*/
bool File::isWritable() const {
    return writable_;
}

/**
 * Retrieves the current filename as a string.
*/
std::string File::getFilename() const {
    return filename_;
}

/**
 * Retrieves the last modified timestamp of the File object.
 * @return The timestamp stored within `last_modified_timestamp_`
*/
timestamp File::getLastModified() const {
    return last_modified_timestamp_;
}

// setters
/**
 * Sets the readable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new readable permission
 * @post
 * 1. The readble member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
*/
void File::setReadable(const bool& new_permission) {
    readable_ = new_permission;
    last_modified_timestamp_ = cr::system_clock::now();    
}

/**
 * Sets the writable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new writable permission
 * @post
 * 1. The writable member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
*/
void File::setWritable(const bool& new_permission) {
    writable_ = new_permission;
    last_modified_timestamp_ = cr::system_clock::now();
}

/**
 * Attempts to set a new filename for the File object.
 * The operation FAILS if:
 * 1. The passed filename is empty or contains spaces
 * 2. The extension of the old and new filenames are not equal.
 * Note: Do not append a default extension to the parameter!
 *
 * @param filename A const reference to a string for the new filename.
 * @return true if the filename was successfully updated, false otherwise.
 * @post
 * 1. If possible, the filename variable is set to that of the parameter
 * 2. If the filename was modified, the last modified attribute is updated to the current system time
*/
bool File::setFilename(const std::string& filename) {
    // checks if filename is empty
    if (filename == "") {
        return false;
    }

    // checks if filename has a space
    for (size_t i = 0; i < filename.size(); i++) {
        if (filename[i] == ' ') {
            return false;
        }
    }

    // checks if the file extensions are not equal by using findFileExtension from FileUtils.cpp
    if (FileUtils::findFileExtension(filename_) != FileUtils::findFileExtension(filename)) {
        return false;
    }

    // can't find anything wrong, updating the filename and system time
    filename_ = filename;
    last_modified_timestamp_ = cr::system_clock::now();
    return true;
}

// given to us in instructions to debug
std::string File::toString() const {
    std::stringstream ss;
    ss << "Filename: " << filename_ << std::endl;
    ss << "Read: " << (readable_ ? "y" : "n") << std::endl;
    ss << "Write: " << (writable_ ? "y" : "n") << std::endl;
    return ss.str();
}
