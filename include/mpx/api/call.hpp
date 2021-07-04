#ifndef MPX_API_CALL_HPP
#define MPX_API_CALL_HPP

namespace mpx::api {
/**
 * @brief Direct call api.
 *
 * This is a trivial wrapper that just calls
 * the funtion.
 */
struct call {
  template <class R, class... Args>
  static R invoke(R (*fp)(Args...), Args... args) {
    return (*fp)(args...);
  }
};
} // namespace mpx::api

#endif
