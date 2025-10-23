#pragma once

#include "Clock.hpp"
#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace FileUtils {

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
 *  1. No extension is found
 *  2. The filename is empty.
 */
std::string findFileExtension(const std::string& filename);

/**
 * Checks if a given filename contains any whitespace characters.
 *
 * A whitespace character is any character matching the STL documentation in the link below.
 *
 * @param filename A const reference to a string representing the filename to check for spaces.
 * @return true if the filename contains one or more whitespace characters, false otherwise.
 * @see https://en.cppreference.com/w/cpp/string/byte/isspace.html
 */
bool hasWhitespaces(const std::string& filename);

/**
 * Converts a timestamp (chrono time_point) into a formatted string representation.
 *
 * @param time_point A timestamp value representing a specific point in time to be converted.
 * @return  A string containing the formatted date & time in the form "YYYY-MM-DD HH:MM:SS"
 */
std::string timestampToString(timestamp time);
};
