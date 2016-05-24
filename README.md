# Asio Extensions (_AsioExt_)

[![Build Status](https://travis-ci.org/timniederhausen/asio-extensions.svg?branch=master)](https://travis-ci.org/timniederhausen/asio-extensions)
[![Build status](https://ci.appveyor.com/api/projects/status/696yog08f0fbpck0/branch/master?svg=true)](https://ci.appveyor.com/project/timniederhausen/asio-extensions/branch/master)

## Feature overview

* `file_handle`: A thin wrapper around a native file handle that supports
  Asio's Stream* concepts.

## Building

Asio Extensions (or short: AsioExt) requires at least a C++03-compliant compiler.
However, not all AsioExt features are usable from C++03 (e.g. movable `file_handle` objects).
These features are enabled based on the C++11/C++14 support of the used compiler.

<!-- todo: compiler support -->

Like Asio, AsioExt is header-only by default.
However, it is also possible to build the AsioExt library in a separate compilation unit.

## Library dependencies:

* Asio 1.10.0+
* [optional] Boost 1.46.0+ (If _Boost.Filesystem_ support is enabled)

## Simple example

```cpp
#include <asioext/file_handle.hpp>
#include <asioext/open_flags.hpp>

#include <asio/write.hpp>

#include <iostream>

int main(int argc, const char* argv[])
{
  try {
    using namespace asioext::open_flags;
    asioext::file_handle file("myfile.txt", access_write | create_always);

    const std::string content = "Hello world";
    asio::write(file, asio::buffer(content));
    return 0;
  } catch (std::exception& e) {
    // Exceptions are used for error reporting here.
    // All functions also offer a non-throwing overload,
    // which takes an asio::error_code& instead.
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }
}
```

## Documentation
The documentation can be found at http://timniederhausen.github.io/asio-extensions.
The URL above points at a copy of this repositories' `gh-pages` branch,
which contains the entire self-contained HTML documentation.

Additionally, the documentation can be generated by building the special
`asioext.doc` target. Note that this target is only available if you have
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) installed.

## License
Please see [LICENSE_1_0.txt](LICENSE_1_0.txt).
