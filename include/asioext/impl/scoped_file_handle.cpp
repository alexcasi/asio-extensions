/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "asioext/scoped_file_handle.hpp"
#include "asioext/open.hpp"

#include "asioext/detail/throw_error.hpp"

ASIOEXT_NS_BEGIN

scoped_file_handle::scoped_file_handle() ASIOEXT_NOEXCEPT
  : handle_()
{
  // ctor
}

scoped_file_handle::scoped_file_handle(file_handle handle) ASIOEXT_NOEXCEPT
  : handle_(handle)
{
  // ctor
}

scoped_file_handle::scoped_file_handle(
    const file_handle::native_handle_type& handle) ASIOEXT_NOEXCEPT
  : handle_(handle)
{
  // ctor
}

scoped_file_handle::~scoped_file_handle()
{
  error_code ec;
  close(ec);
  // error is swallowed
}

#ifdef ASIOEXT_HAS_MOVE

scoped_file_handle::scoped_file_handle(scoped_file_handle&& other) ASIOEXT_NOEXCEPT
  : handle_(other.handle_)
{
  other.handle_.clear();
}

scoped_file_handle& scoped_file_handle::operator=(scoped_file_handle&& other)
{
  if (handle_.is_open())
    handle_.close();

  handle_ = other.handle_;
  other.handle_.clear();
  return *this;
}

#endif

file_handle scoped_file_handle::release() ASIOEXT_NOEXCEPT
{
  file_handle handle = handle_;
  handle_.clear();
  return handle;
}

void scoped_file_handle::reset(file_handle handle)
{
  error_code ec;
  reset(handle, ec);
  detail::throw_error(ec);
}

void scoped_file_handle::reset(file_handle handle,
                               error_code& ec) ASIOEXT_NOEXCEPT
{
  close(ec);
  if (!ec)
    handle_ = handle;
}

ASIOEXT_NS_END
