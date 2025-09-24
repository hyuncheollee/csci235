/*
Hyuncheol Lee
2025/09/20

this file 
*/

#include <iostream>
#include <sstream>
#include "File.hpp"
#include "FileUtils.hpp"

// constructors
File::File() {                                                                              // default constructor
    filename_ = "New_Text_Document.txt";
    readable_ = true;
    writeable_ = true;
}

File::File(const std::string& filename, const bool& isReadable, const bool& isWriteable) {  // parametized constructor
    readable_ = isReadable;
    writeable_ = isWriteable;
    filename_ = filename;
}

// getters
bool File::isReadable() const {
    return readable_;
}   

bool File::isWriteable() const{
    return writeable_;
}

std::string File::getFileName() const{
    return filename_;
}

// setters
void File::setReadable(const bool& new_permission) {
    readable_ = new_permission;
}

void File::setWriteable(const bool& new_permission) {
    writeable_ = new_permission;
}

bool File::setFileName(const std::string& filename) {
    // checks if filename is empty
    if (filename == "") {
        return false;
    }

    // checks if filename has a space
    for (int i = 0; i < filename.size(); i++) {
        if (filename[i] == ' ') {
            return false;
        }
    }

    // checks if the file extensions are not equal by using findFileExtension from FileUtils.cpp
    if (FileUtils::findFileExtension(filename_) != FileUtils::findFileExtension(filename)) {
        return false;
    }

    // can't find anything wrong, updating the filename
    filename_ = filename;
    return true;
}

std::string File::toString() const {
    std::stringstream ss;
    ss << "Filename: " << filename_ << std::endl;
    ss << "Read: " << (readable_ ? "y" : "n") << std::endl;
    ss << "Write: " << (writeable_ ? "y" : "n") << std::endl;
    return ss.str();
}
