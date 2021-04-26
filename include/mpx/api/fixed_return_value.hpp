#ifndef MPX_API_FIXED_RETURN_VALUE_HPP
#define MPX_API_FIXED_RETURN_VALUE_HPP

namespace mpx::api {
/**
 * @brief Return a fixed value from all matching calls.
 *
 * Returns a fixed return value for all calls.
 * With this you can e.g. make all mpi functions return MPI_SUCCESS.
 *
 * @tparam return_value Value to return.
 */
template <auto return_value> struct fixed_fixed_return_value {
  using return_type = decltype(return_value);

  template <class... Args>
  static return_type eval(return_type (*)(Args...), Args...) {
    return return_value;
  }
};
} // namespace mpx::api

#endif