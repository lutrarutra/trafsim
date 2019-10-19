#include "Random.h"

namespace TrafSim
{

Random::Random()
{
    srand(time(nullptr));
}

void Random::distribution_test(int iterations)
{
    const int size = 20;
    int arr[size];
    for (int i = 0; i < size; ++i)
        arr[i] = 0;
    for (int i = 0; i < iterations; ++i)
    {
        int k = std::min(size-1, std::max(0, (int)norm_dist<float>(10, 3)));
        arr[k]++;
    }
    std::string s = "";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < arr[i]; ++j)
        {
            s += "*";
        }
        if(!s.empty())
            std::cout << s << "\n";
        s = "";
    }
}

} // namespace TrafSim