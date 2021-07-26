# See the end of this file for copyright and license terms.

option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_DOCS_HTML "Build documentation in HTML format" ON)
option(BUILD_DOCS_LATEX "Build documentation in LaTEX format" OFF)
option(BUILD_DOCS_RTF "Build documentation in Rich Text Format" OFF)
option(BUILD_DOCS_XML "Build documentation in XML format" OFF)

if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    add_custom_target(neo_docs ALL
        DEPENDS neo
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Building documentation"
        VERBATIM
    )

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    if(BUILD_DOCS_HTML)
        set(neo_BUILD_DOCS_HTML YES)
    else()
        set(neo_BUILD_DOCS_HTML NO)
    endif()

    if(BUILD_DOCS_LATEX)
        set(neo_BUILD_DOCS_LATEX YES)
    else()
        set(neo_BUILD_DOCS_LATEX NO)
    endif()

    if(BUILD_DOCS_RTF)
        set(neo_BUILD_DOCS_RTF YES)
    else()
        set(neo_BUILD_DOCS_RTF NO)
    endif()

    if(BUILD_DOCS_XML)
        set(neo_BUILD_DOCS_XML YES)
    else()
        set(neo_BUILD_DOCS_XML NO)
    endif()
endif()

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
