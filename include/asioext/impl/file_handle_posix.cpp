/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "asioext/file_handle.hpp"

#include "asioext/detail/posix_file_ops.hpp"
#include "asioext/detail/throw_error.hpp"

ASIOEXT_NS_BEGIN

file_handle::file_handle() ASIOEXT_NOEXCEPT
  : handle_(-1)
{
  // ctor
}

bool file_handle::is_open() const ASIOEXT_NOEXCEPT
{
  return handle_ != -1;
}

void file_handle::close(error_code& ec) ASIOEXT_NOEXCEPT
{
  if (handle_ == -1) {
    ec = error_code();
    return;
  }

  detail::posix_file_ops::close(handle_, ec);
  handle_ = -1;
}

void file_handle::clear() ASIOEXT_NOEXCEPT
{
  handle_ = -1;
}

uint64_t file_handle::size(error_code& ec) ASIOEXT_NOEXCEPT
{
  return detail::posix_file_ops::size(handle_, ec);
}

uint64_t file_handle::position(error_code& ec) ASIOEXT_NOEXCEPT
{
  return seek(seek_origin::from_current, 0, ec);
}

uint64_t file_handle::seek(seek_origin origin,
                           int64_t offset,
                           error_code& ec) ASIOEXT_NOEXCEPT
{
  return detail::posix_file_ops::seek(handle_, origin, offset, ec);
}

file_perms file_handle::permissions(error_code& ec) ASIOEXT_NOEXCEPT
{
  return detail::posix_file_ops::permissions(handle_, ec);
}

void file_handle::permissions(file_perms perms,
                              error_code& ec) ASIOEXT_NOEXCEPT
{
  detail::posix_file_ops::permissions(handle_, perms, ec);
}

file_attrs file_handle::attributes(error_code& ec) ASIOEXT_NOEXCEPT
{
  return detail::posix_file_ops::attributes(handle_, ec);
}

void file_handle::attributes(file_attrs attrs,
                             error_code& ec) ASIOEXT_NOEXCEPT
{
  detail::posix_file_ops::attributes(handle_, attrs, ec);
}

ASIOEXT_NS_END
