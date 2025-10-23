#pragma once

#include "File.hpp"
#include <string>

class TextFile : public File {
private:
    std::string content_;

public:
    /**
     * Constructs a new TextFile object.
     *
     * @pre For simplicity, we assume that the extension is that of a text file -- you need not validate it.
     *
     * @param filename  A const reference to a string representing the filename of the text file.
     * @param content   A const reference to a string representing the initial file contents (defaults to an empty string if omitted).
     * @param readable  A boolean indicating whether the file is readable (defaults to true if omitted).
     * @param writable  A boolean indicating whether the file is writable (defaults to true if omitted).
     *
     * @post
     * 1. The filename and permissions are initialized via the base File constructor.
     * 2. The file contents are set to the provided string, or remain empty if none is provided.
     */
    TextFile(
        const std::string& filename,
        const std::string& content = "",
        bool readable = true,
        bool writable = true);

    /**
     * Updates the content of the text file.
     *
     * @param newContent A const reference to a string representing the new file contents.
     * @post
     * 1. The content_ member variable is updated to match the provided string.
     * 2. The last_modified_timestamp_ of the underlying File is updated to the current time
     * specified by the Clock class
     */
    void setContent(const std::string& newContent);

    /**
     * Retrieves the current contents of the text file.
     * @return A string containing the text file's contents.
     */
    std::string getContent() const;

    /**
     * Generates a formatted string representation of the text file.
     *
     * @return A string containing the file's name, permissions, last modified timestamp,
     *         and contents, or "(none)" if the contents are empty.
     */
    std::string toString() const;
};