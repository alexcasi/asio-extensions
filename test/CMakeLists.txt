# Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(sources
	basic_file.cpp
	main.cpp
	open.cpp
	open_flags.cpp
	read_file.cpp
	scoped_file_handle.cpp
	write_file.cpp
)

if (WIN32)
	list(APPEND sources
		win_path.cpp
	)
endif ()

add_executable(asioext.test ${sources})

target_link_libraries(asioext.test asioext)
