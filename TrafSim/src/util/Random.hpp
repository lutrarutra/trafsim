#pragma once

#include <stdlib.h>
#include <ctime> //time
#include <cstdlib>
#include <random> //normal_distribution
#include <fstream>
#include <string>
#include <iostream>

namespace TrafSim
{
class Random
{
public:
    Random();
    // between low - high including low but not high
    template <typename T>
    T rand_int(T low, T high) const
    {
        if(low >= high)
            return high;
        return rand() % high + low;
    }
    // between 0 - high including 0 but not high
    template <typename T>
    T rand_int(T high) const { return rand_int<T>(0, high); };

    template <typename T>
    T norm_dist(T expected_val, T standard_deviation) const
    {
        std::default_random_engine gen(rand_int<unsigned int>(UINT_MAX));
        std::normal_distribution<T> dist(expected_val, standard_deviation);
        return dist(gen);
    }
    //Only for testing purposes
    void distribution_test(int iterations);

private:
};
} // namespace TrafSim