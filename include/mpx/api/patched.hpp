#ifndef MPX_API_PATCHED_HPP
#define MPX_API_PATCHED_HPP

#include <algorithm>
#include <utility>
#include <vector>
#include <any>

namespace mpx::api {
template <class Api> struct patched {
  using void_fun = void (*)(void);

  struct Patch {
    Patch() = default;
    template <class R, class... Args, class F>
    Patch(R (*orig)(Args...), F subst)
        : from(reinterpret_cast<void_fun>(orig)) {
      to = std::function<R(Args...)>{std::move(subst)};
    }

    void_fun from;
    std::any to;
  };

  template <class F>
  static void with_patches(std::vector<Patch> const &patches_, F f) {
    patches() = &patches_;
    f();
    patches() = nullptr;
  }

  template <class R, class... Args>
  static R invoke(R (*fp)(Args...), Args... args) {
    if (not patches()) {
      return Api::invoke(fp, args...);
    }

    auto it = std::find_if(
        patches()->begin(), patches()->end(), [fp](auto const &patch) {
          return patch.from == reinterpret_cast<void_fun>(fp);
        });

    if (it != patches()->end()) {
      auto f = std::any_cast<std::function<R(Args...)>>(it->to);

      return f(args...);
    } else {
      return Api::invoke(fp, args...);
    }
  }

private:
  static auto &patches() {
    static const std::vector<Patch> *m_patches = {};

    return m_patches;
  }
};
} // namespace mpx::api

#endif