#ifndef MPX_SEND_HPP
#define MPX_SEND_HPP

#include <mpx/api.hpp>
#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>

namespace mpx {
template <class Api = default_api, class T>
void send(communicator const &comm, Rank to, Tag tag, T const &data) {
  auto const data_range = data_range_for<T>{}(data);

  Api::eval(&MPI_Send, data_range.data, data_range.type.count,
            data_range.type.type, static_cast<int>(to), static_cast<int>(tag),
            comm);
}
} // namespace mpx

#endif