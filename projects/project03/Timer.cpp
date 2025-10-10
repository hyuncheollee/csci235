#include "Timer.hpp"

void Timer::start()
{
    start_time_ = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    end_time_ = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const
{
    if (end_time_ < start_time_) {
        return 0.0;
    }
    std::chrono::duration<double> elapsed_seconds = end_time_ - start_time_;
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);
    return ms.count();
}
