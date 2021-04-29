#ifndef MPX_API_LOG_HPP
#define MPX_API_LOG_HPP

#include <any>
#include <optional>
#include <vector>

namespace mpx::api {
/**
 * @brief Log entry for a signle call.
 *
 * This records a single call logged by @c log.
 */
struct log_entry {
  /** Pointer to function that was called. */
  std::any callee;
  /** Arguments passed to the call. */
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
  static void invoke(R (*fp)(Args...), Args... args) {
    if (call_log())
      call_log()->emplace_back(log_entry{fp, {args...}});

    Api::invoke(fp, args...);
  }

  template <class F> static auto with_log(F f) {
    std::vector<log_entry> log;
    call_log() = &log;
    f();
    call_log() = nullptr;
    return log;
  }

private:
  static auto &call_log() {
    static std::vector<log_entry> *m_log = nullptr;

    return m_log;
  }
};

namespace detail {
template <class... Ts>
bool compare(std::vector<std::any> const &anys, Ts... vals) {
  auto it = anys.begin();
  return (sizeof...(Ts) == anys.size()) and
         ((std::any_cast<Ts>(*it++) == vals) && ...);
}
} // namespace detail

/**
 * @brief Compare a logged call to a function pointer.
 *
 * @param entry The long entry to compare.
 * @param fp Callee to compare
 * @param args Arguments to compare.
 * @return True if the logged call matches the callee and the arguements.
 */
template <class R, class... Args>
bool call_compare(log_entry const &entry, R (*fp)(Args...), Args... args) {
  return (std::any_cast<decltype(fp)>(entry.callee) == fp) and
         detail::compare(entry.args, args...);
}
} // namespace mpx::api

#endif