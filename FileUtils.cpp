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

this file
*/

#include <iostream>
using namespace std;

int main() {
    cout << "HELLO";
}