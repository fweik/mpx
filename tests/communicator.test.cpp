#include <doctest/doctest.h>

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>

TEST_CASE("rank") {
  mpx::communicator comm{};

  auto const r = mpx::rank<mpx::api::null>(comm);
  CHECK(static_cast<int>(r) == 0);
}

TEST_CASE("size") {
  mpx::communicator comm{};

  auto const r = mpx::size<mpx::api::null>(comm);
  CHECK(r == 1);
}
