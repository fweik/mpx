#include <doctest/doctest.h>

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>

TEST_CASE("rank") {
  mpx::communicator comm{};
  mpx::api::patched<>::patch(&MPI_Comm_rank,
                             [](mpx::communicator, int *rank) -> int {
                               *rank = 0;
                               return MPI_SUCCESS;
                             });

  auto const r = mpx::rank<mpx::api::patched<>>(comm);
  CHECK(static_cast<int>(r) == 0);
}

TEST_CASE("size") {
  mpx::communicator comm{};

  mpx::api::patched<>::patch(&MPI_Comm_size,
                             [](mpx::communicator, int *size) -> int {
                               *size = 1;
                               return MPI_SUCCESS;
                             });

  auto const r = mpx::size<mpx::api::patched<>>(comm);
  CHECK(r == 1);
}
