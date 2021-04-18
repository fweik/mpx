#include <doctest/doctest.h>

#include <mpx/request.hpp>

template <class T> bool any_compare(std::any const &a, T const &val) {
  return std::any_cast<T const &>(a) == val;
}

TEST_CASE("test") {
  using mpx::api::log_only;

  mpx::request req{};
  mpx::test<log_only>(req);

  auto const &last_log = log_only::call_log().back();
  CHECK(any_compare(last_log.callee, &MPI_Test));
  CHECK(any_compare(last_log.args.at(0), std::addressof(req)));
}

TEST_CASE("wait") {
  using mpx::api::log_only;

  mpx::request req{};
  mpx::wait<log_only>(req);

  auto const &last_log = log_only::call_log().back();
  CHECK(any_compare(last_log.callee, &MPI_Wait));
  CHECK(any_compare(last_log.args.at(0), std::addressof(req)));
  CHECK(any_compare(last_log.args.at(1), MPI_STATUSES_IGNORE));
}