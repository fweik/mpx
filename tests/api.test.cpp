#include <doctest/doctest.h>

#include <mpx/api.hpp>

TEST_CASE("call") {
  CHECK(mpx::api::call::eval(static_cast<int (*)()>([]() { return 5; })) == 5);
}