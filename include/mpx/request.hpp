#ifndef MPX_FUTURE_HPP
#define MPX_FUTURE_HPP

#include <mpx/api.hpp>
#include <mpx/exception.hpp>

#include <mpi.h>

#include <utility>

namespace mpx {
using request = MPI_Request;

template <class Api = api::mpi> bool test(request &req) {
  int ret = 0;
  Api::call(&MPI_Test, std::addressof(req), std::addressof(ret),
            MPI_STATUS_IGNORE);

  return ret != 0;
}

template <class Api = api::mpi> void wait(request &req) {
  Api::call(&MPI_Wait, std::addressof(req), MPI_STATUS_IGNORE);
}
} // namespace mpx

#endif