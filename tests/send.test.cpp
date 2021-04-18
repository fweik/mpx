#include <doctest/doctest.h>

#include <mpx/send.hpp>

TEST_CASE("blocking send") {
  mpx::communicator comm{};

  mpx::send<mpx::api::null>(comm, mpx::Rank{4}, mpx::Tag{3}, 5);
}