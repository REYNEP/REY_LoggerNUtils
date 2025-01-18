#[[                 ********** Boost Software License - Version 1.0 - August 17th, 2003 **********
Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and accompa
nying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute, and transm
it the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the Software is fu
rnished to do so, all subject to the following:

The copyright notices in the Software and this entire statement, including the above license grant, this restriction and
the following disclaimer, must be included in all copies of the Software, in whole or in part, and all derivative works
of the Software, unless such copies or derivative works are solely in the form of machine-executable object code genera
ted by a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WAR
RANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGH
T HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#                           *************** END Boost Software License BLOCK ***************                          ]]
#                   *************** The Original Code is Copyright (C) 2025, REYNEP ***************                   ]]


cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project("REY_LoggerNUtils_PROJECT" VERSION 0.1)

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------
    set(SRC
        "REY_Logger.cpp"
    )

    set(INC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
# --------------------

# --------------------
add_library                (REY_LoggerNUtils ${SRC})
target_include_directories (REY_LoggerNUtils PUBLIC ${INC})
set_target_properties      (REY_LoggerNUtils  PROPERTIES  OUTPUT_NAME "lib-REY_LoggerNUtils"  PREFIX "")

# --------fmt---------
    #                                    input:- ${REY_FETCH_FMT_BASE_DIR]
    include(${CMAKE_CURRENT_SOURCE_DIR}/REY_FetchV4/REY_FetchV4.fmt.cmake)  # Output:- fmt::fmt
    target_link_libraries  (REY_LoggerNUtils PUBLIC fmt::fmt)

# -----bli-assert-----
    if(WIN32)                                                       # for Windows operating system in general
        target_link_libraries  (REY_LoggerNUtils PUBLIC Dbghelp.lib Version.lib Shlwapi.lib)
    elseif(MSVC OR MSYS OR MINGW)                                   # for detecting Windows compilers
        target_link_libraries  (REY_LoggerNUtils PUBLIC Dbghelp.lib Version.lib Shlwapi.lib)
    elseif(APPLE)                                                   # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
        target_link_libraries  (REY_LoggerNUtils PUBLIC execinfo)
    elseif(UNIX AND NOT APPLE)                                      # for Linux, BSD, Solaris, Minix
        target_link_libraries  (REY_LoggerNUtils PUBLIC execinfo)
    endif()
    # From:- https://stackoverflow.com/a/40152725

# ------install-------
    install(TARGETS REY_LoggerNUtils
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/.install)
        # Same Destination is used for installing "fmt::fmt" --> Check: `REY_FetchV4.fmt.cmake`

# Install header files
    install(FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/REY_Logger.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/REY_LoggerEXT.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/REY_Utils.hh
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/.install/include/REY_LoggerNUtils)

