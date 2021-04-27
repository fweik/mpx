
#ifndef MPX_API_NULL_HPP
#define MPX_API_NULL_HPP

namespace mpx::api {
/**
 * @brief Null api.
 *
 * This is a trivial wrapper does nothing.
 * The calee is required to return void.
 */
struct null {
  template <class... Args> static void invoke(void (*)(Args...), Args...) {}
};
} // namespace mpx::api

#endif