#ifndef MPX_RECV_HPP
#define MPX_RECV_HPP

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>

namespace mpx {
template <class T, class Api = default_api>
void recv(communicator const &comm, Rank to, Tag tag, T &data) {
  auto const data_range = data_range_for<T>{}(data);

  Api::eval(&MPI_Recv, data_range.data, data_range.type.count,
            data_range.type.type, static_cast<int>(to), static_cast<int>(tag),
            comm);
}
} // namespace mpx

#endif