# See the end of this file for copyright and license terms.

add_executable(demo)

target_link_libraries(demo PRIVATE neo)

target_sources(demo PRIVATE
    ./error.c
    ./nref_borrowed.c
    ./nref_simple.c
    ./main.c
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
