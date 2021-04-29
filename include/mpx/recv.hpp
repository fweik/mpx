#ifndef MPX_RECV_HPP
#define MPX_RECV_HPP

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>

namespace mpx {
template <class Api = default_api, class T>
void recv(communicator const &comm, Rank to, Tag tag, T &data) {
  auto const data_range = data_range_for<T>::get(data);

  Api::invoke(&MPI_Recv, data_range.data, data_range.count, data_range.type,
              static_cast<int>(to), static_cast<int>(tag), comm,
              MPI_STATUSES_IGNORE);
}
} // namespace mpx

#endif