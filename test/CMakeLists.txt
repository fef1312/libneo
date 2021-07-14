# See the end of this file for copyright and license terms.

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.6
)
FetchContent_MakeAvailable(Catch2)

add_executable(neo_test neo_test.cpp)

target_compile_features(neo_test PRIVATE cxx_std_17)
target_link_libraries(neo_test PRIVATE neo Catch2::Catch2)

add_test(NAME neo COMMAND neo_test)

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
