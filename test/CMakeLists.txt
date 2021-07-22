# See the end of this file for copyright and license terms.

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.6
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

add_executable(neo_test neo_test.cpp)
include(nbuf/nbuf.cmake)
include(string/string.cmake)

target_sources(neo_test PRIVATE
    list.cpp
    nref.cpp
)

target_link_libraries(neo_test PRIVATE neo Catch2::Catch2)

catch_discover_tests(neo_test)

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
