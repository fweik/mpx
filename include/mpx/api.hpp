#ifndef MPX_API_HPP
#define MPX_API_HPP

#include <mpx/api/call.hpp>
#include <mpx/api/log.hpp>
#include <mpx/api/null.hpp>
#include <mpx/api/throw_on_error.hpp>
#include <mpx/api/fixed_return_value.hpp>

namespace mpx {
using default_api = api::throw_on_error<0>;
}

#endif