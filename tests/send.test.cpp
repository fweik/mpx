#include <doctest/doctest.h>

#include <mpx/send.hpp>

TEST_CASE("send") {
  using api = mpx::api::log<mpx::api::null>;

  mpx::communicator comm;
  mpx::Rank to{5};
  mpx::Tag tag{6};
  const int data = 7;

  auto const &log = api::scope_log();
  mpx::send<api>(comm, to, tag, data);

  call_compare(log.front(), &MPI_Send, comm, to, tag, data);
}