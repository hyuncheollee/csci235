#include "Clock.hpp"

/**
 * @brief Gets the current system time.
 * @return A timestamp representing the current time.
 */
timestamp Clock::now() const
{
    return cr::system_clock::now();
}
