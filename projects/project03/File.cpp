#include "File.hpp"

const std::string File::DEFAULT_FILENAME = "New_Text_Document.txt";
const std::string File::DEFAULT_EXTENSION = "txt";
std::shared_ptr<Clock> File::system_clock_ = std::make_shared<Clock>();

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

std::string File::getFilename() const
{
    return filename_;
}

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

bool File::isReadable() const
{
    return readable_;
}

void File::setReadable(const bool& new_permission)
{
    readable_ = new_permission;
    updateLastModified();
}

bool File::isWritable() const
{
    return writable_;
}

void File::setWritable(const bool& new_permission)
{
    writable_ = new_permission;
    updateLastModified();
}

void File::updateLastModified()
{
    last_modified_timestamp_ = system_clock_->now();
}

timestamp File::getLastModified() const
{
    return last_modified_timestamp_;
}

std::string File::toString() const
{
    std::stringstream ss;
    ss << "Filename: " << filename_ << std::endl;
    ss << "Read: " << (readable_ ? "y" : "n") << std::endl;
    ss << "Write: " << (writable_ ? "y" : "n") << std::endl;
    ss << "Last Modified: " << (FileUtils::timestampToString(last_modified_timestamp_)) << std::endl;
    return ss.str();
}

void File::setClock(std::shared_ptr<Clock> new_clock)
{
    system_clock_ = new_clock;
}

std::ostream& operator<<(std::ostream& os, const File& f)
{
    os << f.toString();
    return os;
}