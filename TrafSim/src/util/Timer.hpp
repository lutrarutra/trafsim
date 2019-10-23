#pragma once

#include <chrono>
#include <iostream>

namespace TrafSim
{

class Timer
{
public:
    Timer() : m_start(std::chrono::high_resolution_clock::now()){};
    //Returns duration from last reset or creation of this timer in milliseconds
    template <typename T>
    T msFromReset() const
    {
        //Use microseconds for more accurate timer
        std::chrono::duration<T, std::micro> duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_start);
        //micro / milli = 1000, so we get milliseconds
        return duration.count() / std::milli::den;
    }
    void reset() { m_start = std::chrono::high_resolution_clock::now(); }

private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};

// This will be for measuring performance
class PerformanceTimer : public Timer
{
public:
    PerformanceTimer() : Timer()
    {
    }
    ~PerformanceTimer()
    {
        std::cout << msFromReset<float>() << "\n";
    }
};

} // namespace TrafSim