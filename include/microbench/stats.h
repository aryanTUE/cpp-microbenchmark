#pragma once
#include <vector>
#include <numeric>
#include <algorithm>

namespace microbench {
namespace stats {

template <typename T>
T getMean(const std::vector<T>& data) {
    if (data.empty()) return 0;
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum / data.size();
}

template <typename T>
T getPercentile(std::vector<T> data, double p) {
    if (data.empty()) return 0;
    std::sort(data.begin(), data.end());
    size_t index = static_cast<size_t>((p / 100.0) * (data.size() - 1));
    return data[index];
}

} // namespace stats
} // namespace microbench