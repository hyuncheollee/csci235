/*
Hyuncheol Lee
2025/11/15

this file is the header file for FilterList
*/

#pragma once

#include "ImageFilter.hpp"

#include <string>
#include <vector>

class FilterList {
private:
    // filters are stored in the order they were added
    std::vector<ImageFilter*> filters_;

public:
    /**
     * Default constructor.
     * Starts with an empty list of filters.
     */
    FilterList();

    /**
     * Gets the number of filters currently in the list.
     *
     * @return The number of filters in the list as an integer.
     */
    int size() const;

    /**
     * Returns a list of all of the ImageFilter pointers
     * within the FilterList.
     *
     * @return A std::vector<ImageFilter*> containing all the filters.
     */
    std::vector<ImageFilter*> getFilters() const;

    /**
     * Adds a filter to the end of the filter list.
     *
     * @param f A pointer to the ImageFilter to add.
     * @throws std::invalid_argument if the provided filter pointer is nullptr.
     *
     * @note Don't make a copy of the filter, just store the pointer.
     */
    void addLastFilter(ImageFilter* f);

    /**
     * Removes the last filter from the list.
     *
     * @return true if a filter was removed, false if the list was empty.
     *
     * @note This does not delete the filter. The caller is responsible
     *       for freeing the memory.
     */
    bool removeLastFilter();

    /**
     * Generates a string representation of the filter list of the form:
     *
     * FilterList
     *   1. <filter 1>::name()
     *   ...
     *   N. <filter N>::name()
     *
     * or if no filters have been added:
     *
     * FilterList:
     *   (no filters added)
     *
     * @return A formatted string as described above.
     */
    std::string toString() const;

    /**
     * Applies all filters in the list to an ImageFile in the order
     * they were added (first added → first applied).
     *
     * @param img A (non-const) reference to an ImageFile to apply the filters to.
     */
    void applyAll(ImageFile& img) const;
};
