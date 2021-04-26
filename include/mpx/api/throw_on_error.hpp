#ifndef MPX_API_THROW_ON_ERROR_HPP
#define MPX_API_THROW_ON_ERROR_HPP

namespace mpx::api {
/**
 * @brief Convert error code into exception.
 *
 * This wrapper compares the return value  of functions
 * returning an error code to an value indicating success.
 * If it differs an exception which captuers the error code
 * is thrown. Effectivly this turns error codes into exceptions.
 *
 * @tparam ok_code Success error code
 */
template <auto ok_code = 0> struct throw_on_error {
  using error_code_type = decltype(ok_code);

  struct exception {
    error_code_type error_code;
  };

  template <class R, class... Args>
  static decltype(auto) eval(R (*fp)(Args...), Args... args) {
    return (*fp)(args...);
  }

  template <class... Args>
  static void eval(error_code_type (*fp)(Args...), Args... args) {
    auto const error_code = (*fp)(args...);

    if (error_code != ok_code) {
      throw exception{error_code};
    }
  }
};
} // namespace mpx::api

#endif