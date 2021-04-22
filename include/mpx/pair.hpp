#ifndef MPX_PAIR_HPP
#define MPX_PAIR_HPP

#include <mpx/api.hpp>
#include <mpx/data_type.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace mpx {
template <class T, class U>
struct data_type_for<
    std::pair<T, U>,
    std::enable_if_t<std::is_standard_layout_v<std::pair<T, U>>>> {

  template <class Api = api::mpi> static DataType get() {
    static MPI_Datatype m_type = []() {
      auto const first_type = data_type_for<T>::template get<Api>();
      auto const second_type = data_type_for<U>::template get<Api>();

      const int lengths[] = {first_type.count, second_type.count};
      const MPI_Datatype types[] = {first_type.type, second_type.type};

      using Pair = std::pair<T, U>;
      const MPI_Aint displacements[] = {offsetof(Pair, first),
                                        offsetof(Pair, second)};
      MPI_Datatype pair_type;
      Api::call(&MPI_Type_create_struct, 2, lengths, displacements, types,
                &pair_type);
      Api::call(&MPI_Type_commit, &pair_type);

      return pair_type;
    }();

    return {m_type, 1};
  }
};
} // namespace mpx

#endif