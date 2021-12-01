#include <fmt/format.h>
#include <range/v3/distance.hpp>
#include <range/v3/functional/comparisons.hpp>
#include <range/v3/view/adjacent_filter.hpp>

#include <span>
#include <array>

namespace {

auto count_adj_increases(const std::span<const double> input) {
    if (input.empty()) {
        return 0l;
    }
    return ranges::distance(ranges::views::adjacent_filter(input, ranges::less())) - 1;
}

auto test(const std::span<const double> input) {
    fmt::print("testing: {{{}}}\n", fmt::join(input, ", "));
    fmt::print("measurements increased {} time(s)\n", count_adj_increases(input));
}

} // namespace

int main() {
    test(std::array{1.0, 2.0, 2.0, 3.0, 2.0});
    test(std::array{1.0});
    test(std::array<double, 0>{});
    test(std::array{1.0, 2.0, 2.0, 3.0, 2.0, 1.0, 44.0, 55.0, 55.0, 33.0});
    test(std::array{3.0, 2.0, 1.0});
}
