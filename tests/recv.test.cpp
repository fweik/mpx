#include <doctest/doctest.h>

#include <mpx/recv.hpp>

TEST_CASE("recv") {
  using mpx::api::fixed_return_value;
  using mpx::api::patched;
  using api = patched<fixed_return_value<MPI_SUCCESS>>;

  mpx::communicator comm;
  mpx::Rank from{5};
  mpx::Tag tag{6};
  int data;

  api::with_patches(
      {{&MPI_Recv,
        [](void *buf, int count, MPI_Datatype datatype, int source, int tag,
           MPI_Comm comm, MPI_Status *status) {
          CHECK(count == 1);
          CHECK(datatype == MPI_INT);
          CHECK(source == 5);
          CHECK(tag == 6);

          *reinterpret_cast<int *>(buf) = 5;
          return MPI_SUCCESS;
        }}},
      [&]() {
        mpx::recv<api>(comm, from, tag, data); });

  CHECK(data == 5);
}

TEST_CASE("recv") {
  using mpx::api::fixed_return_value;
  using mpx::api::patched;
  using api = patched<fixed_return_value<MPI_SUCCESS>>;

  mpx::communicator comm;
  mpx::Rank from{5};
  mpx::Tag tag{6};
  int data;

  api::with_patches(
      {{&MPI_Recv,
        [](void *buf, int count, MPI_Datatype datatype, int source, int tag,
           MPI_Comm comm, MPI_Status *status) {
          CHECK(count == 1);
          CHECK(datatype == MPI_INT);
          CHECK(source == 5);
          CHECK(tag == 6);

          *reinterpret_cast<int *>(buf) = 5;
          return MPI_SUCCESS;
        }}},
      [&]() {
        CHECK(5 == mpx::recv<int, api>(comm, from, tag)); });
}