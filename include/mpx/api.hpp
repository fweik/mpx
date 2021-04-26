#ifndef MPX_API_HPP
#define MPX_API_HPP

#include <mpx/api/call.hpp>
#include <mpx/api/null.hpp>
#include <mpx/api/throw_on_error.hpp>

namespace mpx {
using default_api = api::throw_on_error<0>;
}

#endif