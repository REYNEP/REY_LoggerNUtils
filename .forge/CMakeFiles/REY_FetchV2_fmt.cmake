# --------------------
#  INPUT Options:-
#       ${REY_FIND_FMT_PATHS}     ---> We won't fetch unless this is EMPTY-STRING/NOT-DEFINED
#       ${REY_FETCH_FMT_BASE_DIR} ---> Stuff will be fetched into this DIR
# OUTPUT Options:- 
#       ${fmt::fmt} ---------> this is a "Target"
#                              this is How you use it:-
#                                   target_link_libraries(idk fmt::fmt)
#                                   target_include_directories(idk PUBLIC fmt::fmt)
# --------------------

# I will be releasing a series of files line these ones. Named ".REY_FetchV2_<library_Name>.cmake"
#   These will serve as an ROBUST / Lower-Level (but well DOCUMENTED) Alternative to CMAKE_FETCH!

# Pseudocode for this file
# --------------------
# if (REY_FIND_FMT_PATHS != "")
    # find_library(fmtd.lib)
    # find_path(fmt/core.h)
    # USE:- REY_FIND_FMT_PATHS
    # Check FOUND / LOG FATAL ERROR
# else()
    # if(NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt )
        # git clone https://github.com/fmtlib/fmt
        # add_subdirectory(fmt)
    # else()
        # if((NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt/CMakeLists.txt) OR (NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt/src/fmt.cc))
            # LOG FATAL ERROR
        # else()
            # add_subdirectory(fmt)
        # endif()
    # endif()
# endif()
# --------------------

# --------------------
    if(NOT DEFINED ${CMAKE_BUILD_TYPE})
        set(CMAKE_BUILD_TYPE Debug)
    endif()
# --------------------
if (  (DEFINED REY_FIND_FMT_PATHS)   AND   (${REY_FIND_FMT_PATHS} NOT STREQUAL "")  )
        # ================================ FINDING fmtd.lib =================================
            find_library(REY_search_fmt_lib
                NAMES
                    fmtd      # UNIX/MAC
                    fmt       # Windows
                DOC
                    ""
                PATHS
                    ${REY_FIND_FMT_PATHS}
                    ${REY_FIND_FMT_PATHS}/lib
                    ${REY_FIND_FMT_PATHS}/libs
                    ${REY_FIND_FMT_PATHS}/extern-libs
                PATH_SUFFIXES
                    Debug
                    Release
                    Lib         # Windows
                    lib         # UNIX/MAC

                NO_CACHE
                #NO_DEFAULT_PATH
            )

            if (EXISTS ${REY_search_fmt_lib})
                set(REY_SEARCH_FMT_LIB ${REY_search_fmt_lib} CACHE STRING "" FORCE)
                message(STATUS "[REY_FetchV2_FMT]")
                message(STATUS "    Found 1 File:- ${REY_search_fmt_lib}")
            endif()
        # ================================ FINDING fmtd.lib =================================


        # =============================== FINDING fmt/core.h ================================
            find_path(REY_search_fmt_inc
                NAMES
                    fmt/core.h
                PATHS
                    ${REY_FIND_FMT_PATHS}
                    ${REY_FIND_FMT_PATHS}/include
                    ${REY_FIND_FMT_PATHS}/includes
                    ${REY_FIND_FMT_PATHS}/extern-includes
                PATH_SUFFIXES
                    fmt
                    fmt/include
                    include/fmt
                NO_CACHE
            )

            if (REY_search_fmt_inc)
                set(REY_SEARCH_FMT_INCLUDE ${REY_search_fmt_inc} CACHE STRING "" FORCE)
                message(STATUS "[REY_FetchV2_FMT]")
                message(STATUS "    Found include dir: ${REY_search_fmt_inc}")
            endif()
        # =============================== FINDING fmt/core.h ================================


        # =============================== if BOTH ARE FOUND =================================
            if (REY_SEARCH_FMT_LIB AND REY_SEARCH_FMT_INCLUDE)
                add_library(fmt::fmt STATIC IMPORTED)
                set_target_properties(fmt::fmt PROPERTIES
                    IMPORTED_LOCATION ${REY_SEARCH_FMT_LIB}
                    INTERFACE_INCLUDE_DIRECTORIES ${REY_SEARCH_FMT_INCLUDE}
                )
                message(STATUS "[REY_FetchV2_FMT]")
                message(STATUS "    Created imported target fmt::fmt")
                message(STATUS "    [cached] REY_SEARCH_FMT_LIB:-    ${REY_SEARCH_FMT_LIB}")
                message(STATUS "    [cached] REY_SEARCH_FMT_INCLUDE: ${REY_SEARCH_FMT_INCLUDE}")
            else ()
                message(STATUS "REY_FIND_FMT_PATHS:- ${REY_FIND_FMT_PATHS}")
                message(STATUS "REY_search_fmt_lib:- ${REY_search_fmt_lib}")
                message(STATUS "REY_search_fmt_inc:- ${REY_search_fmt_inc}")
                message(FATAL_ERROR "REY_FIND_FMT_PATHS is defined but Could not find fmt library. 
                                    Please Undefine it or make it EMPTY-STRING, if you want us to automatically `git clone fmt`")
            endif()
        # =============================== if BOTH ARE FOUND =================================
else()


    if( (NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt) )
        message(STATUS "Fetching github.com/fmtlib/fmt inside ${REY_FETCH_FMT_BASE_DIR}")
        message(STATUS "Download Progress being logged inside ${REY_FETCH_FMT_BASE_DIR}/fmt_Download_stdout.log ")
        execute_process(
            #COMMAND cmd /c "git clone https://github.com/fmtlib/fmt > fmt_Download.log 2>&1"
            COMMAND          git clone https://github.com/fmtlib/fmt

            #COMMAND        "git clone https://github.com/fmtlib/fmt"
            # With Quotation marks, it doesn't redirect stdout to OUTPUT_FILE/VARIABLE

            WORKING_DIRECTORY ${REY_FETCH_FMT_BASE_DIR}

            OUTPUT_VARIABLE tmp_stdout               ERROR_VARIABLE tmp_stdout
            # OUTPUT_FILE     fmt_Download_stdout.log  ERROR_FILE     fmt_Download_stdout.log
            # Both doesn't work @ the same time

            TIMEOUT 10              # seconds
            COMMAND_ECHO STDOUT     # output's the part after "COMMAND" few lines above
        )
        file(WRITE "${REY_FETCH_FMT_BASE_DIR}/fmt_Download_stdout.log" "${tmp_stdout}\n")
        message(STATUS "tmp_stdout:- ${tmp_stdout}")
        message(STATUS "Fetching Done")


        add_subdirectory(${REY_FETCH_FMT_BASE_DIR}/fmt)     #Output:- fmt::fmt
    elseif((NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt/CMakeLists.txt) OR (NOT EXISTS ${REY_FETCH_FMT_BASE_DIR}/fmt/src/fmt.cc))
        message(STATUS "[REY_FetchV2_FMT]")
        message(STATUS "     REY_FETCH_FMT_BASE_DIR:- ${REY_FETCH_FMT_BASE_DIR}")
        message(STATUS "                                      ")
        message(STATUS "[DIR]REY_FETCH_FMT_BASE_DIR/fmt exists")
        message(STATUS "     but it doesn't contain `fmt/CMakeLists.txt` or `fmt/src/fmt.cc`")
        message(STATUS "                                      ")
        message(STATUS "                & as long as it exists -> `git clone fmt` won't work")

        message(FATAL_ERROR "ERROR INFO Has been Logged above\n
                             ERROR:- REY_FETCH_FMT_BASE_DIR/fmt exists, but it's not a proper GIT CLONE\n
                             see .REY_FetchV2_fmt.cmake TOP Documentation part for INPUT-Settings/Variables")
    else()
        add_subdirectory(${REY_FETCH_FMT_BASE_DIR}/fmt)     #Output:- fmt::fmt
    endif()


endif()

