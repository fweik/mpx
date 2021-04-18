#ifndef MPX_COMMUNICATOR_HPP
#define MPX_COMMUNICATOR_HPP

#include <mpx/api.hpp>
#include <mpx/exception.hpp>

#include <mpi.h>

namespace mpx {
class Rank {
  int rank;

public:
  explicit Rank(int rank) : rank(rank) {}
  explicit operator int() const { return rank; }
};

class Tag {
  int tag;

public:
  explicit Tag(int tag) : tag(tag) {}
  explicit operator int() const { return tag; }
};

using communicator = MPI_Comm;
static auto world = MPI_COMM_WORLD;
static auto self = MPI_COMM_SELF;

template <class Api = api::mpi> Rank rank(communicator const &comm) {
  int rank;
  Api::call(&MPI_Comm_rank, comm, std::addressof(rank));

  return Rank{rank};
}

template <class Api = api::mpi> int size(communicator const &comm) {
  int size;
  Api::call(&MPI_Comm_size, comm, std::addressof(size));

  return size;
}
} // namespace mpx

#endif