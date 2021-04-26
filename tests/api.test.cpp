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

TEST_CASE("compare") { CHECK(mpx::api::compare({1, 2., 3}, 1, 2., 3)); }

TEST_CASE("log") {
  using api = mpx::api::log<mpx::api::null>;

  void (*fp)(int, float) = [](int, float) {};
  auto log = api::with_log([=]() { api::eval(fp, 5, 3.1f); });

  CHECK(call_compare(log.at(0), fp, 5, 3.1f));
}

TEST_CASE("fixed_return_value") {
  auto constexpr return_value = 13;

  CHECK(mpx::api::fixed_return_value<return_value>::eval(
            static_cast<int (*)()>([]() { return 5; })) == return_value);
}