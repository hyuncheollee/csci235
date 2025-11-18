/*
Hyuncheol Lee
2025/11/15

this file is the source file for FilterList
*/

#include "FilterList.hpp"
#include "ImageFile.hpp"

#include <sstream>
#include <stdexcept>

/**
 * Default Constructor -- you may initialize whatever members you deem necessary
 *
 * @note Hint: I only have one private member variable; reference the getters.
 */
FilterList::FilterList() : filters_() {}

/**
 * @brief Gets the number of filters currently in the list.
 *
 * @return The number of filters in the list as an integer
 */
int FilterList::size() const {
    return static_cast<int>(filters_.size());
}

/**
 * @brief Returns a list of all of the ImageFilters pointers
 * within the FilterList.
 *
 * @return A std::vector<ImageFilter*> containing all the filters
 */
std::vector<ImageFilter*> FilterList::getFilters() const {
    return filters_;
}

/**
 * @brief Adds a filter to the end of the filter list.
 *
 * @param f A pointer to the ImageFilter to add
 * @throws std::invalid_argument Thrown if the provided filter pointer is nullptr.
 *
 * @note Don't make a copy of the dereferenced pointer -- just use the pointer value/address itself
 */
void FilterList::addLastFilter(ImageFilter* f) {
    if (f == nullptr) {
        throw std::invalid_argument("Filter pointer cannot be nullptr");
    }
    
    filters_.push_back(f);
}

/**
 * @brief Removes the last filter from the list.
 *
 * @return Returns true if a filter was successfully removed,
 * otherwise returns false if the list was empty.
 *
 * @note The caller is expected to manage the de-allocation of the pointer.
 * i.e. This function does not release the memory of the removed filter
 */
bool FilterList::removeLastFilter() {
    if (filters_.empty()) {
        return false;
    }

    filters_.pop_back();

    return true;
}

/**
 * @brief Generates a string representation of the filter list of the form:
 *
 * FilterList
 *  1. <filter 1>::name()
 *  ...
 *  N. <filter N>::name()
 *
 * or if no filters have been added:
 *
 * FilterList:
 *    (no filters added)
 *
 *
 * @return A string containing whose first line is "FilterList", and
 * names of all the filters in the list, each numbered on a new line and indented (for readability),
 * as seen in the format above.
 *
 * @example If we had a FilterList, where we add an InvertFilter first, and then
 * a red ColorFilter, we might have something like:
 *
 * FilterList
 *  1. Invert Filter
 *  2. Color Filter [255,0,0]
 */
std::string FilterList::toString() const {
    std::ostringstream out;

    if (filters_.empty()) {
        out << "FilterList:\n"
            << "  (no filters added)";
    } 
    
    else {
        out << "FilterList\n";
        
        for (int i = 0; i < static_cast<int>(filters_.size()); ++i) {
            out << "  " << (i + 1) << ". " << filters_[i]->name();
            
            if (i + 1 < static_cast<int>(filters_.size())) {
                out << "\n";
            }
        }
    }

    return out.str();
}

/**
 * @brief Applies all filters in the list to an ImageFile in the order
 * they were added (e.g. first to add => first applied, etc.)
 *
 * @param img A (non-const) reference to an ImageFile to apply the filters to
 */
void FilterList::applyAll(ImageFile& img) const {
    // apply filters in the order they were added
    for (ImageFilter* f : filters_) {

        if (f != nullptr) {
            f -> apply(img);
        }
    }
}