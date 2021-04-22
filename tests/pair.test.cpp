#include <doctest/doctest.h>

#include <mpx/pair.hpp>

#include <cstddef>

TEST_CASE("type for pair is implemented") {
  auto const pair_type =
      mpx::data_type_for<std::pair<char, double>>::get<mpx::api::log_only>();
}