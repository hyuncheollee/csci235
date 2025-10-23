#include "FileUtils.hpp"

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
std::string FileUtils::findFileExtension(const std::string& filename)
{
    if (filename.empty()) {
        return "";
    }

    for (int i = filename.size() - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            return filename.substr(i, filename.size() - i);
        }
    }

    return "";
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
bool FileUtils::hasWhitespaces(const std::string& filename)
{
    for (const char& c : filename) {
        if (std::isspace(c)) {
            return true;
        }
    }

    return false;
}

/**
 * Converts a timestamp (chrono time_point) into a formatted string representation.
 *
 * @param time_point A timestamp value representing a specific point in time to be converted.
 * @return  A string containing the formatted date & time in the form "YYYY-MM-DD HH:MM:SS"
 */
std::string FileUtils::timestampToString(timestamp time_point)
{
    std::time_t tt = cr::system_clock::to_time_t(time_point);
    std::tm streamable_time = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&streamable_time, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
