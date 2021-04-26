#ifndef MPX_API_LOG_HPP
#define MPX_API_LOG_HPP

#include <any>
#include <optional>
#include <vector>

namespace mpx::api {
struct log_entry {
  std::any callee;

  std::vector<std::any> args;
};

/**
 * @brief Log all calls.
 *
 * This wrapper loggs all function calls
 * and than forwards the calls to another api.
 *
 * @tparam Api Backend api to which the calls are forwarded.
 */
template <class Api> struct log {
  template <class R, class... Args>
  static void eval(R (*fp)(Args...), Args... args) {
    call_log().emplace_back(log_entry{fp, {args...}});

    Api::eval(fp, args...);
  }

  template <class F> static auto with_log(F f) {
    call_log().clear();
    f();
    return call_log();
  }

private:
  static auto &call_log() {
    static std::vector<log_entry> m_log;

    return m_log;
  }
};

template <class... Ts>
bool compare(std::vector<std::any> const &anys, Ts... vals) {
  auto it = anys.begin();
  return (sizeof...(Ts) == anys.size()) and
         ((std::any_cast<Ts>(*it++) == vals) && ...);
}

template <class R, class... Args>
bool call_compare(log_entry const &entry, R (*fp)(Args...), Args... args) {
  return (std::any_cast<decltype(fp)>(entry.callee) == fp) and
         compare(entry.args, args...);
}
} // namespace mpx::api

#endif