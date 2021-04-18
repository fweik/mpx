#ifndef MPX_SEND_HPP
#define MPX_SEND_HPP

#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>
#include <mpx/api.hpp>

#include <mpi.h>

namespace mpx {
template <class Api = mpx::api::mpi, class T>
void send(communicator const &comm, Rank to, Tag tag, T const &data) {
  auto const data_range = data_range_for<T>{}(data);

  Api::call(&MPI_Send, data_range.data, data_range.type.count,
            data_range.type.type, static_cast<int>(to), static_cast<int>(tag),
            comm);
}
} // namespace mpx

#endif