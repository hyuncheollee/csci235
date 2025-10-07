#include <string>
#include <TextFile.hpp>

TextFile::TextFile() {

}

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
TextFile::TextFile(const std::string& filename, const std::string& content, bool& readable, bool& writable) {       // parametized constructor
    filename_ = filename;
    content_ = content;
    readable_ = readable;
    writable_ = writable;
}