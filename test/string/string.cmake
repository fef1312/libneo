# See the end of this file for copyright and license terms.

include(string/utf/utf.cmake)

target_sources(neo_test PRIVATE
    string/i2nstr.cpp
    string/leftpad.cpp
    string/nstr.cpp
    string/nstrcat.cpp
    string/nstrcmp.cpp
    string/nstrdup.cpp
    string/u2nstr.cpp
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
