#pragma once

#include <chrono>

/**
 * @class Timer
 * @brief A simple high-resolution timer class for measuring elapsed time.
 *
 * This class provides basic functionalities to start and stop a timer,
 * and get the elapsed time in seconds between the start and stop calls.
 *
 * It uses std::chrono::high_resolution_clock (not system_clock) for higher precision timing!
 */
class Timer {
public:
    /**
     * @brief Default constructor for the Timer.
     */
    Timer() = default;

    /**
     * @brief Starts the timer.
     *
     * Records the current time as the starting point of the interval.
     */
    void start();

    /**
     * @brief Stops the timer.
     *
     * Records the current time as the ending point of the interval.
     */
    void stop();

    /**
     * @brief Calculates the elapsed time between start() and stop() calls.
     * @return The elapsed time in milliseconds (as a double).
     */
    double elapsed() const;

private:
    /// @brief The type for the high-resolution clock's time point.
    using time_point_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

    /// @brief The time point when the timer was started.
    time_point_t start_time_ {};

    /// @brief The time point when the timer was stopped.
    time_point_t end_time_ {};
};
