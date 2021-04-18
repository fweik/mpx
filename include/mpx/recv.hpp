#ifndef MPX_RECV_HPP
#define MPX_RECV_HPP

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>

#include <mpi.h>

namespace mpx {
template <class Api = api::mpi, class T>
void recv(communicator const &comm, Rank to, Tag tag, T &data) {
  auto const data_range = data_range_for<T>{}(data);

  Api::call(&MPI_Recv, data_range.data, data_range.type.count,
            data_range.type.type, static_cast<int>(to), static_cast<int>(tag),
            comm, MPI_STATUS_IGNORE);
}

template <class T, class Api = api::mpi>
std::enable_if_t<std::is_default_constructible_v<T>, T>
recv(communicator const &comm, Rank to, Tag tag) {
  T data;

  recv(comm, to, tag, data);

  return data;
}
} // namespace mpx

#endif