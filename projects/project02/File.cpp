#include "File.hpp"

const std::string File::DEFAULT_FILENAME = "New_Text_Document.txt";
const std::string File::DEFAULT_EXTENSION = "txt";
std::shared_ptr<Clock> File::system_clock_ = std::make_shared<Clock>();

/**
 * Constructs a new File object.
 *
 * @param filename   A const reference to a string for the initial filename, defaulting to "New_Text_Document.txt" if the parameter is omitted.
 * @param isReadable A const reference to a boolean for the readable permission, defaults to true if omitted.
 * @param isWritable A const reference to a boolean for the writable permission, defaults to true if omitted..
 * @post
 * Sets the File's filename_ such that:
 * 1. If the parameter contains spaces or has no characters at all, the default filename is used
 * 2. If the parameter has no extension (no `period` characters whatsoever), .txt is appended to the filename & used
 * 3. If the parameter has an empty extension (a `period` characters followed by no characters), txt is appended to the filename & used
 * 4. Otherwise, the parameter filename is used as is
 * Note: A filename like `.env` or `.log` IS allowed (ie. filenames containing only the extension)!
 *
 * Sets the current system time as the file's last modified timestamp.
 */
File::File(const std::string& filename, const bool& isReadable, const bool& isWritable)
    : filename_ { filename }
    , readable_ { isReadable }
    , writable_ { isWritable }
{
    updateLastModified();
    if (filename.empty() || FileUtils::hasWhitespaces(filename_)) {
        filename_ = DEFAULT_FILENAME;
        return;
    }
    appendDefaultExtension();
}

/**
 * @brief Appends a default extension to the filename if one is not already present
 * @post Modifies the `filename_` member variable if necessary
 */
void File::appendDefaultExtension()
{
    std::string extension = FileUtils::findFileExtension(filename_);
    if (extension.empty()) {
        filename_ += ".";
        extension = ".";
    }

    if (extension == ".") {
        filename_ += DEFAULT_EXTENSION;
    }
}
/**
 * @brief Updates the  `last_modified_timestamp_` member to the current
 * time by calling the `now()` method on the `system_clock_` object.
 *
 * @note Do not modify this!
 */
void File::updateLastModified()
{
    last_modified_timestamp_ = system_clock_->now();
}

/**
 * @brief Sets the clock implementation to be used by this class.
 *
 * This method allows dependency injection of a custom clock, providing
 * this makes testing your code easier + faster
 *
 * @param c Reference to a Clock instance that provides the current time.
 * @note Do not modify this!
 *
 * @see https://builtin.com/articles/dependency-injection (in case you're curious)
 */
void File::setClock(std::shared_ptr<Clock> new_clock)
{
    system_clock_ = new_clock;
}

/**
 * Retrieves the current filename as a string.
 */
std::string File::getFilename() const
{
    return filename_;
}

/**
 * Attempts to set a new filename for the File object.
 * The operation FAILS if:
 * 1. The passed filename is empty or contains spaces
 * 2. The extension of the old and new filenames are not equal.
 * Note: Do not append a default extension to the parameter!
 *
 * @param filename A const reference to a string for the new filename.
 * @return true if the filename was successfully updated, false otherwise.
 * @post
 * 1. If possible, the filename variable is set to that of the parameter
 * 2. If the filename was modified, the last modified attribute is updated to the current system time
 */
bool File::setFilename(const std::string& filename)
{
    if (filename.empty() || FileUtils::hasWhitespaces(filename)) {
        return false;
    }

    std::string old_extension = FileUtils::findFileExtension(filename_);
    std::string new_extension = FileUtils::findFileExtension(filename);
    if (new_extension != old_extension) {
        return false;
    }

    filename_ = filename;
    updateLastModified();
    return true;
}

/**
 * Retrieves the current readable permission as a boolean.
 */
bool File::isReadable() const
{
    return readable_;
}

/**
 * Sets the readable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new readable permission
 * @post
 * 1. The readble member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
 */
void File::setReadable(const bool& new_permission)
{
    readable_ = new_permission;
    updateLastModified();
}

/**
 * Retrieves the current writable permission as a boolean.
 */
bool File::isWritable() const
{
    return writable_;
}

/**
 * Sets the writable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new writable permission
 * @post
 * 1. The writable member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
 */
void File::setWritable(const bool& new_permission)
{
    writable_ = new_permission;
    updateLastModified();
}

/**
 * Retrieves the last modified timestamp of the File object.
 */
timestamp File::getLastModified() const
{
    return last_modified_timestamp_;
}

/**
 * Generates a formatted string representation of the File object's properties.
 * @return A string containing the file's name, permissions, and last modified date.
 */
std::string File::toString() const
{
    std::stringstream ss;
    ss << "Filename: " << filename_ << std::endl;
    ss << "Read: " << (readable_ ? "y" : "n") << std::endl;
    ss << "Write: " << (writable_ ? "y" : "n") << std::endl;
    ss << "Last Modified: " << (FileUtils::timestampToString(last_modified_timestamp_)) << std::endl;
    return ss.str();
}