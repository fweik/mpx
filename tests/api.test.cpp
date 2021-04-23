#include <doctest/doctest.h>

#include <mpx/api.hpp>

TEST_CASE("call") {
  CHECK(mpx::api::call::eval(static_cast<int (*)()>([]() { return 5; })) == 5);
}

TEST_CASE("null") {
  CHECK_NOTHROW(
      mpx::api::null::eval(static_cast<void (*)()>([]() { throw 0; })));
}
