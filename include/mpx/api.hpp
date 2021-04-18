#ifndef MPX_API_HPP
#define MPX_API_HPP

#include <mpx/exception.hpp>

#include <mpi.h>

#include <any>
#include <cstdint>
#include <vector>

namespace mpx::api {
struct mpi {
  template <class... Args> static void call(int (*fp)(Args...), Args... args) {
    check_error_code((*fp)(args...));
  }
};

struct null {
  template <class... Args> static void call(int (*fp)(Args...), Args... args) {
    if constexpr (std::is_invocable_v<decltype(fp), MPI_Comm, int *>) {
      if (fp == &MPI_Comm_rank) {
        *std::get<1>(std::tie(args...)) = 0;
      }
      if (fp == &MPI_Comm_size) {
        *std::get<1>(std::tie(args...)) = 1;
      }
    }
  }
};

template <class Api> struct log {
  struct log_entry {
    std::any callee;

    std::vector<std::any> args;
  };

  static auto &call_log() {
    static std::vector<log_entry> m_log;

    return m_log;
  }

  template <class... Args> static void call(int (*fp)(Args...), Args... args) {
    call_log().emplace_back(log_entry{fp, {args...}});

    Api::call(fp, args...);
  }
};

using log_only = log<null>;
} // namespace mpx::api

#endif