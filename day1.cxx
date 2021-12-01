#include <fmt/format.h>
#include <range/v3/distance.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/functional/identity.hpp>
#include <range/v3/algorithm/count_if.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/adjacent_filter.hpp>
#include <range/v3/numeric/adjacent_difference.hpp>

#include <span>
#include <array>

namespace {

auto count_adj_increases(const std::span<const double> input) {
    std::vector<double> diffs(input.size());
    ranges::adjacent_difference(input, diffs);
    const auto increases = diffs | ranges::views::drop(1)
            | ranges::views::transform([](auto d) { return d > 0.0; });
    return ranges::count_if(increases, ranges::identity());
}

auto count_adj_increases2(const std::span<const double> input) {
    if (input.empty()) {
        return 0l;
    }
    return ranges::distance(ranges::views::adjacent_filter(input, ranges::less())) - 1;
}

auto test(const std::span<const double> input) {
    fmt::print("testing: {{{}}}\n", fmt::join(input, ", "));
    fmt::print("measurements increased {} time(s)\n", count_adj_increases(input));
    fmt::print("measurements increased {} time(s)\n", count_adj_increases2(input));
}

} // namespace

int main() {
    test(std::array{1.0, 2.0, 2.0, 3.0, 2.0});
    test(std::array{1.0});
    test(std::array<double, 0>{});
    test(std::array{1.0, 2.0, 2.0, 3.0, 2.0, 1.0, 44.0, 55.0, 55.0, 33.0});
    test(std::array{3.0, 2.0, 1.0});
}
