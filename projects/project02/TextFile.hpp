/*
Hyuncheol Lee
2025/10/05

this file deals with the given file's text data
*/

#pragma once

#include "File.hpp"
#include <string>

class TextFile : public File {
private:
    std::string content_;       // A string representing the actual text stored within the file

public:
    // constructors
    /**
     * Constructs a new TextFile object.
     *
     * @pre For simplicity, we assume that the filename extension is that of a text file -- you need not validate it.
     *
     * @param filename A const reference to a string representing the filename of the text file.
     * @param content A const reference to a string representing the initial file contents (defaults to an empty string if omitted).
     * @param readable A boolean indicating whether the file is readable (defaults to true if omitted).
     * @param writable A boolean indicating whether the file is writable (defaults to true if omitted).
     *
     * @post
     * 1. The filename and permissions are initialized via the base File constructor.
     * 2. The file contents are set to the provided string, or remain empty if none is provided.
     *
     * @note You should be initializing the base class explicitly (refer to lecture)
    */
    TextFile(const std::string& filename, const std::string& content = "", bool readable = true, bool writable = true);
    
    // getters
    /**
     * Retrieves the current contents of the text file.
     * @return A string containing the text file's contents.
    */
    std::string getContent() const;

    // setters
    /**
     * Updates the content of the text file.
     *
     * @param newContent A const reference to a string representing the new file contents.
     * @post
     * 1. The content_ member variable is updated to match the provided string.
     * 2. The last_modified_timestamp_ of the underlying File is updated to the current time
     * specified by Clock::now.
     *
     * @note Hint: You will need to modify `File` (ie. the base class) to allow you to actually update the last modified timestamp.
    */
    void setContent(const std::string& newContent);
};
