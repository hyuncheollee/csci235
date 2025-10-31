#include "FileUtils.hpp"
#include <string>

std::string FileUtils::timestampToString(timestamp time_point)
{
    std::time_t tt = cr::system_clock::to_time_t(time_point);
    std::tm streamable_time = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&streamable_time, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// YOUR CODE BELOW HERE --------

/*
Hyuncheol Lee
2025/09/09

this file declares:
findFileExtension
hasWhiteSpaces
*/

/**
 * Extracts the file extension from a given filename.
 *
 * We define the file extension as the string containing:
 * 1. The last period within the filename
 * 2. All characters after that period
 *
 * @pre Assume the given filename has no spaces
 * @param filename A const reference to a string representing the filename from which to find the extension.
 * @return A string containing the extracted file extension or an empty string if:
 * 1. No extension is found
 * 2. The filename is empty.
*/    
std::string FileUtils::findFileExtension(const std::string& filename) {
        std::string empty = "";

        // returns empty string if file name is empty
        if (filename == "") {
            return filename;
        }
                
        // finds the extension if the file name isn't empty

        // get the extension name but from the back
        int i = filename.size() - 1;
        while (i >= 0 && filename[i] != '.') {
            empty += filename[i];
            i--;            
        }

        // will return empty string if the file doesn't have an extension
        if (empty.size() == filename.size()) {
            return "";
        } 

        // reverse the string
        std::string extension = ".";
        for (int i = empty.size() - 1; i >= 0; i--) {
            extension += empty[i];
        }

        // here's the result
        return extension;
    }

/**
 * Checks if a given filename contains any whitespace characters.
 *
 * A whitespace character is any character matching the STL documentation in the link below.
 *
 * @param filename A const reference to a string representing the filename to check for spaces.
 * @return true if the filename contains one or more whitespace characters, false otherwise.
 * @see https://en.cppreference.com/w/cpp/string/byte/isspace.html
*/    
bool FileUtils::hasWhitespaces(const std::string& filename) {
        // https://en.cppreference.com/w/cpp/string/byte/isspace.html
        
        // iterates through the string
        for (size_t i = 0; i < filename.size(); i++) {
            // returns true if we found a whitespace (' ', \n, \v, \f, \r, \t)
            if (filename[i] == ' ' || filename[i] == '\n' || filename[i] == '\v' || filename[i] == '\f' || filename[i] == '\r' || filename[i] == '\t') {
                return true;
            }
        }
        
        // ran through the file name and couldn't find a whitespace
        return false;
    }