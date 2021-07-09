# See the end of this file for copyright and license terms.

set(JEMALLOC_SRCDIR "${CMAKE_SOURCE_DIR}/contrib/jemalloc")
set(JEMALLOC_PREFIX "${CMAKE_BINARY_DIR}/contrib/jemalloc")

include(ExternalProject)
ExternalProject_Add(
    libjemalloc
    SOURCE_DIR ${JEMALLOC_SRCDIR}
    TMP_DIR ${JEMALLOC_PREFIX}
    STAMP_DIR ${JEMALLOC_PREFIX}
    CONFIGURE_COMMAND ${JEMALLOC_SRCDIR}/autogen.sh --without-export --enable-static --disable-cxx --srcdir ${JEMALLOC_SRCDIR} --prefix=${JEMALLOC_PREFIX} --build=x86_64-pc-linux-gnu --host=x86_64-pc-linux-gnu
    PREFIX ${JEMALLOC_SRCDIR}
    BUILD_COMMAND make build_lib_static
    BUILD_IN_SOURCE 1
    BUILD_BYPRODUCTS ${JEMALLOC_PREFIX}/lib/libjemalloc.a
)

add_library(jemalloc STATIC IMPORTED GLOBAL)
add_dependencies(jemalloc libjemalloc)
set_property(
    TARGET jemalloc
    PROPERTY IMPORTED_LOCATION ${JEMALLOC_PREFIX}/lib/libjemalloc.a
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
