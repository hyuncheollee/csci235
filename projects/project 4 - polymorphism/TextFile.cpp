#include "TextFile.hpp"

TextFile::TextFile(const std::string& filename, const std::string& content, bool readable, bool writable)
    : File(filename, readable, writable)
    , content_ { content }
{
}

void TextFile::setContent(const std::string& newContent)
{
    content_ = newContent;
    File::updateLastModified();
}

std::string TextFile::getContent() const
{
    return content_;
}

std::string TextFile::toString() const
{
    std::stringstream ss;
    ss << File::toString();
    ss << "Content: " << (content_.empty() ? "(none)" : content_) << std::endl;
    return ss.str();
}