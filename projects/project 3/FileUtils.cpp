#include "FileUtils.hpp"

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

bool FileUtils::hasWhitespaces(const std::string& filename)
{
    for (const char& c : filename) {
        if (std::isspace(c)) {
            return true;
        }
    }

    return false;
}

std::string FileUtils::timestampToString(timestamp time_point)
{
    std::time_t tt = cr::system_clock::to_time_t(time_point);
    std::tm streamable_time = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&streamable_time, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}