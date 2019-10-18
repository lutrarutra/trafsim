#pragma once

#include <chrono>

namespace TrafSim
{
class Timer
{
public:
    Timer() : start_(std::chrono::high_resolution_clock::now()){};
    //Returns duration from last reset or creation of this timer in milliseconds
    template <typename T>
    T msFromReset() const
    {
        //Use microseconds for more accurate timer
        std::chrono::duration<T, std::micro> duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_);
        //micro / milli = 1000, so we get milliseconds
        return duration.count() / std::milli::den;
    }
    void reset() { start_ = std::chrono::high_resolution_clock::now(); }

private:
    std::chrono::time_point<std::chrono::steady_clock> start_;
};
} // namespace TrafSim