/*
Hyuncheol Lee
2025/09/20

this is the hpp file for File.cpp where I will declare stuff
*/

#pragma once 

#include <string>
#include "FileUtils.hpp"

class File {
private:
    std::string filename_;                  // A string containing the filename of the File object
    bool readable_;                         // A boolean containing the `read` permission of the File
    bool writable_;                         // A boolean containing the `write` permission of the File
    timestamp last_modified_timestamp_;     // A string containing the time the file was last updated

public:
    // constructors
    File();                                                                                                 // default constructor
    File(const std::string& filename, const bool& isReadable = true, const bool& isWritable = true);        // parametized constructor
    
    // getters
    bool isReadable() const;                // retrieves file's read access
    bool isWritable() const;                // retrieves file's write access
    std::string getFilename() const;        // retrieves name of file
    timestamp getLastModified() const;      // retrieves most recent time of chance

    // setters
    void setReadable(const bool& new_permission);       // updates file's read access
    void setWritable(const bool& new_permission);       // updates file's write access
    bool setFilename(const std::string& filename);      // gives the file a new name
    
    // test and debug
    std::string toString() const;       // given in the instructions
};
