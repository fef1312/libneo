# See the end of this file for copyright and license terms.

add_library(neo STATIC)

target_link_options(neo INTERFACE -T${CMAKE_CURRENT_SOURCE_DIR}/src/neo.ld)

execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TOLOWER "${HOST_ARCH}" HOST_ARCH)
execute_process(COMMAND uname OUTPUT_VARIABLE HOST_OS OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TOLOWER "${HOST_OS}" HOST_OS)

set(TARGET_ARCH "${HOST_ARCH}" CACHE STRING "Target architecture")
set(TARGET_OS "${HOST_OS}" CACHE STRING "Target operating system")

configure_file(
    ./include/neo/buildconfig.h.in
    ${CMAKE_BINARY_DIR}/include/neo/buildconfig.h
)

target_include_directories(neo PUBLIC ../include)
target_include_directories(neo PRIVATE
    ./include
    ${CMAKE_BINARY_DIR}/include
)

target_sources(neo PRIVATE
    ./error.c
    ./list.c
    ./nalloc.c
    ./nref.c
)

include(./string/string.cmake)

# This file is part of libneo.
# Copyright (c) 2021 Fefie <owo@fef.moe>.
#
# libneo is non-violent software: you may only use, redistribute,
# and/or modify it under the terms of the CNPLv6+ as found in
# the LICENSE file in the source code root directory or at
# <https://git.pixie.town/thufie/CNPL>.
#
# libneo comes with ABSOLUTELY NO WARRANTY, to the extent
# permitted by applicable law.  See the CNPLv6+ for details.
