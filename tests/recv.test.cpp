#include <doctest/doctest.h>

#include <mpx/recv.hpp>

#include <doctest/doctest.h>

#include <mpx/send.hpp>

TEST_CASE("blocking recv") {
  mpx::communicator comm{};

  auto const r = mpx::recv<int, mpx::api::null>(comm, mpx::Rank{4}, mpx::Tag{3});
}

TEST_CASE("blocking recv") {
  mpx::communicator comm{};

  int res;
  mpx::recv<mpx::api::null>(comm, mpx::Rank{4}, mpx::Tag{3}, res);
}