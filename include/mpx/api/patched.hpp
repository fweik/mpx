#ifndef MPX_API_PATCHED_HPP
#define MPX_API_PATCHED_HPP

#include <algorithm>
#include <utility>
#include <vector>

namespace mpx::api {
template <class Api> struct patched {
  using void_fun = void (*)(void);

  struct Patch {
    Patch() = default;
    template <class R, class... Args, class F>
    Patch(R (*orig)(Args...), F subst)
        : from(reinterpret_cast<void_fun>(orig)) {
      R (*fp)(Args...) = subst;
      to = reinterpret_cast<void_fun>(fp);
    }

    void_fun from;
    void_fun to;
  };

  template <class F>
  static void with_patches(std::vector<Patch> const &patches_, F f) {
    patches() = &patches_;
    f();
    patches() = nullptr;
  }

  template <class R, class... Args>
  static R eval(R (*fp)(Args...), Args... args) {
    if (not patches()) {
      return Api::eval(fp, args...);
    }

    auto it = std::find_if(
        patches()->begin(), patches()->end(), [fp](auto const &patch) {
          return patch.from == reinterpret_cast<void_fun>(fp);
        });

    if (it != patches()->end()) {
      return (*reinterpret_cast<decltype(fp)>(it->to))(args...);
    } else {
      return Api::eval(fp, args...);
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