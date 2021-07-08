# See the end of this file for copyright and license terms.

add_library(neo)

add_compile_options(-nostdlib -nodefaultlibs)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")

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
    ./entry.c
)

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
