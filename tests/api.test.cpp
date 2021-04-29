#include <doctest/doctest.h>

#include <mpx/api.hpp>

TEST_CASE("call") {
  CHECK(mpx::api::call::invoke(static_cast<int (*)()>([]() { return 5; })) ==
        5);
}

TEST_CASE("null") {
  CHECK_NOTHROW(
      mpx::api::null::invoke(static_cast<void (*)()>([]() { throw 0; })));
}

TEST_CASE("throw_on_error") {
  CHECK_NOTHROW(mpx::api::throw_on_error<5>::invoke(
      static_cast<int (*)()>([]() { return 5; })));
  CHECK_THROWS(mpx::api::throw_on_error<4>::invoke(
      static_cast<int (*)()>([]() { return 5; })));
}

TEST_CASE("compare") { CHECK(mpx::api::detail::compare({1, 2., 3}, 1, 2., 3)); }

TEST_CASE("log") {
  using api = mpx::api::log<mpx::api::null>;

  void (*fp)(int, float) = [](int, float) {};
  auto log = api::with_log([=]() { api::invoke(fp, 5, 3.1f); });

  CHECK(call_compare(log.at(0), fp, 5, 3.1f));
}

TEST_CASE("fixed_return_value") {
  auto constexpr return_value = 13;

  CHECK(mpx::api::fixed_return_value<return_value>::invoke(
            static_cast<int (*)()>([]() { return 5; })) == return_value);
}

TEST_CASE("Patch") {
  bool (*orig)(int) = [](int) -> bool { return false; };
  auto subst = [](int) -> bool { return false; };

  auto patch = mpx::api::patched<mpx::api::null>::Patch(orig, subst);

  using void_fun = mpx::api::patched<mpx::api::null>::void_fun;

  CHECK(patch.from == void_fun(orig));
  CHECK(patch.to == void_fun(static_cast<bool (*)(int)>(subst)));
}

TEST_CASE("patched") {
  enum { ORIG, SUBST };

  int (*orig)(int) = [](int) -> int { return ORIG; };
  auto subst = [](int) -> int { return SUBST; };

  using api = mpx::api::patched<mpx::api::call>;

  /* Without patch list */
  CHECK(api::invoke(orig, 5) == ORIG);
  /* With patch list, but function is not in list */
  api::with_patches({}, [=]() { CHECK(api::invoke(orig, 5) == ORIG); });
  /* With patch list, function is in list */
  api::with_patches({{orig, subst}},
                    [=]() { CHECK(api::invoke(orig, 5) == SUBST); });
}
