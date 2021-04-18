#include <doctest/doctest.h>

#include <mpx/exception.hpp>

TEST_CASE("check_error_code throws on error code") {
  CHECK_THROWS(mpx::check_error_code(MPI_ERR_BUFFER));
  CHECK_NOTHROW(mpx::check_error_code(MPI_SUCCESS));
}