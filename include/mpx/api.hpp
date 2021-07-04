#ifndef MPX_API_HPP
#define MPX_API_HPP

#include <mpx/api/call.hpp>
#include <mpx/api/log.hpp>
#include <mpx/api/null.hpp>
#include <mpx/api/throw_on_error.hpp>
#include <mpx/api/fixed_return_value.hpp>
#include <mpx/api/patched.hpp>

#ifndef MPX_DEFAULT_API
#define MPX_DEFAULT_API api::throw_on_error<0, api::call> 
#endif

namespace mpx {
using default_api = MPX_DEFAULT_API;
}

#endif