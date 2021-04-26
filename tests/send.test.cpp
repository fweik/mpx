#include <doctest/doctest.h>

#include <mpx/send.hpp>

TEST_CASE("send") {
  using api = mpx::api::log<mpx::api::fixed_return_value<MPI_SUCCESS>>;

  mpx::communicator comm;
  mpx::Rank to{5};
  mpx::Tag tag{6};
  const int data = 7;

  auto log = api::with_log([&]() { mpx::send<api>(comm, to, tag, data); });
  CHECK(call_compare(log.front(), &MPI_Send, static_cast<const void *>(&data),
                     1, MPI_INT, static_cast<int>(to), static_cast<int>(tag),
                     comm));
}