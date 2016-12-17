/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ASIOEXT_IMPL_SCOPEDFILEHANDLE_WIN_CPP
#define ASIOEXT_IMPL_SCOPEDFILEHANDLE_WIN_CPP

#include "asioext/scoped_file_handle.hpp"

#include "asioext/detail/win_file_ops.hpp"
#include "asioext/detail/win_path.hpp"
#include "asioext/detail/throw_error.hpp"

ASIOEXT_NS_BEGIN

scoped_file_handle::scoped_file_handle(const char* filename, uint32_t flags)
{
  open(filename, flags);
}

scoped_file_handle::scoped_file_handle(const char* filename,
                                       uint32_t flags,
                                       error_code& ec) ASIOEXT_NOEXCEPT
{
  open(filename, flags, ec);
}

#if defined(ASIOEXT_HAS_BOOST_FILESYSTEM)

scoped_file_handle::scoped_file_handle(const boost::filesystem::path& filename,
                                       uint32_t flags)
{
  open(filename, flags);
}

scoped_file_handle::scoped_file_handle(const boost::filesystem::path& filename,
                                       uint32_t flags,
                                       error_code& ec) ASIOEXT_NOEXCEPT
  : handle_(detail::win_file_ops::open(filename.c_str(), flags, ec))
{
  // ctor
}

#endif

void scoped_file_handle::open(const char* filename,
                              uint32_t flags,
                              error_code& ec) ASIOEXT_NOEXCEPT
{
  if (handle_.is_open()) {
    handle_.close(ec);
    if (ec) return;
  }

  detail::win_path p(filename, std::strlen(filename), ec);
  if (!ec)
    handle_ = detail::win_file_ops::open(p.c_str(), flags, ec);
}

#if defined(ASIOEXT_HAS_BOOST_FILESYSTEM)

void scoped_file_handle::open(const boost::filesystem::path& filename,
                              uint32_t flags,
                              error_code& ec) ASIOEXT_NOEXCEPT
{
  if (handle_.is_open()) {
    handle_.close(ec);
    if (ec) return;
  }

  handle_ = detail::win_file_ops::open(filename.c_str(), flags, ec);
}

#endif

ASIOEXT_NS_END

#endif
