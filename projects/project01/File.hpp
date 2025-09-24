/*
Hyuncheol Lee
2025/09/20

this is the hpp file for File.cpp where I will declare stuff
*/

#include <iostream>

class File {
private:
    std::string filename_;
    bool readable_;
    bool writeable_;

public:
    // constructors
    File();                                                                                 // default constructor
    File(const std::string& filename, const bool& isReadable, const bool& isWriteable);     // parametized constructor
    
    // getters
    bool isReadable() const;
    bool isWriteable() const;
    std::string getFileName() const;

    // setters
    void setReadable(const bool& new_permission);
    void setWriteable(const bool& new_permission);
    bool setFileName(const std::string& filename);
    
    // test
    std::string toString() const;
};
