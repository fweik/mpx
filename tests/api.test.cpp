#include <doctest/doctest.h>

#include <mpx/api.hpp>

TEST_CASE("call") {
  CHECK(mpx::api::call::eval(static_cast<int (*)()>([]() { return 5; })) == 5);
}

TEST_CASE("null") {
  CHECK_NOTHROW(
      mpx::api::null::eval(static_cast<void (*)()>([]() { throw 0; })));
}

TEST_CASE("throw_on_error") {
  CHECK_NOTHROW(mpx::api::throw_on_error<5>::eval(
      static_cast<int (*)()>([]() { return 5; })));
  CHECK_THROWS(mpx::api::throw_on_error<4>::eval(
      static_cast<int (*)()>([]() { return 5; })));
}