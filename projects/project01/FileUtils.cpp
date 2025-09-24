#include "FileUtils.hpp"

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

this file has functions:
findFileExtension
hasWhiteSpaces
*/

#include <iostream>
#include "FileUtils.hpp"

namespace FileUtils {
    std::string findFileExtension(const std::string& fileName) {
        std::string empty = "";

        // returns empty string if file name is empty
        if (fileName == "") {
            return fileName;
        }
                
        // finds the extension if the file name isn't empty

        // get the extension name but from the back
        int i = fileName.size() - 1;
        while (i >= 0 && fileName[i] != '.') {
            empty += fileName[i];
            i--;            
        }

        // will return empty string if the file doesn't have an extension
        if (empty.size() == fileName.size()) {
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

    bool hasWhitespaces(const std::string& fileName) {
        // https://en.cppreference.com/w/cpp/string/byte/isspace.html

        // iterates through the string
        for (int i = 0; i < fileName.size(); i++) {
            // returns true if we found a whitespace (' ', \n, \v, \f, \r, \t)
            if (fileName[i] == ' ' || fileName[i] == '\n' || fileName[i] == '\v' || fileName[i] == '\f' || fileName[i] == '\r' || fileName[i] == '\t') {
                return true;
            }
        }
        
        // ran through the file name and couldn't find a whitespace
        return false;
    }
}
