#pragma once

#include <chrono>

namespace cr = std::chrono;
using timestamp = cr::time_point<cr::system_clock>;

/**
 * A clock class for fetching the current time.
 * DO NOT MODIFY!
 */
class Clock {

public:
    /**
     * @brief Gets the current system time.
     * @return A timestamp representing the current time.
     */
    timestamp now() const;
};
