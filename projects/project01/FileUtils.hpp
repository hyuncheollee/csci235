#pragma once

#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

// This is a namespace alias so we don't have to keep writing
// std::chrono (which is long)
namespace cr = std::chrono;

// Also another alias, but for a specific type instead of an entire
// namespace.
using timestamp = cr::time_point<cr::system_clock>;

// BE CAREFUL AND DO NOT OVER-USE THESE -- IT CAN MAKE YOUR
// CODE MORE CONFUSING TO OTHER PEOPLE IF YOU USE A LOT OF THEM.

namespace FileUtils {

/**
 * Converts a timestamp (chrono time_point) into a formatted string representation.
 *
 * @param time_point A timestamp value representing a specific point in time to be converted.
 * @return  A string containing the formatted date & time in the form "YYYY-MM-DD HH:MM:SS"
 */
std::string timestampToString(timestamp time);

// YOUR CODE BELOW HERE
// DO NOT MODIFY ABOVE ----

};

/*
Hyuncheol Lee
2025/09/09

this file 
*/

