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

# --------------------
    set(Git_Link "https://github.com/fmtlib/fmt")
    set(Git_Name fmt
        # git clone <link> ----> auto creates a Directory. This variable should store that name
    )
    set(Git_SubModule
        # ${CMAKE_CURRENT_SOURCE_DIR}/${Git_Name}
        # Should be a FULL PATH
            # We will assume that this path ---> Exists
            # If this is not EMPTY-STRINGS ----> THIS WILL BE USED
            #                              |---> ${REY_FETCH_${TN}_BASE_DIR} won't be used
    )
    set(Git_CheckFiles
        ${Git_Name}/CMakeLists.txt
        ${Git_Name}/src/fmt.cc
    # ${Git_Name}/REY_Logger.cpp

    # ${Git_Name}/src/fmt.cc
    # ${Git_Name} folder itself is inside ${REY_FETCH_${TN}_BASE_DIR} --> We will handle that part
    )
    set(Binary_Names
        # REY_LoggerNUtils.lib
            fmtd      # UNIX/MAC
            fmt       # Windows
        # *Possible Binary Names/Hints --> Our job is to find any one of these possibilities
    )
    set(Header_Name fmt/core.h)
    set(Target_Name
        # You should set this to what the author ORIGINALLY let the TARGET NAME be inside "${Git_Link}/CMakeLists.txt"
        # REY_LoggerNUtils
        # REY_LoggerNUtils --> will prolly output 'libREY_LoggerNUtils.lib'
        # ex1
        fmt::fmt
        #  fmt::fmt it's a name that "fmt" authors decided to go by
    )
# --------------------
#  INPUT Options:-
#       All the things above & below before Pseudocode
#     Variations:-
#       1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if]
#       2. Git_SubModule ---------------> Git SubModule     [elseif]
#       3. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
#
# OUTPUT Options:- 
#       ${REY_FOUND_${TN}_LIBRARY}  ---> CACHED String to where ${Binary_Names} is located
#       ${REY_FOUND_${TN}_INCLUDE}  ---> CACHED String to where ${Header_Name}  is located
#       ${lib_${TN}} 
#   e.g.  lib_REY_${TN} ---------> this is a "Target"
#                              this is How you use it:-
#                                   target_link_libraries(idk lib_${TN})
#                                   target_include_directories(idk PUBLIC lib_${TN})
# --------------------
    set(Tool_Name 
        fmt
        # Tool_Name = CMAKE Variables will be created based on this. List of variables below inside set(TN)
        # Tool = "External Library" but i really don't like calling SMALL Stuffs "Library" yk
            # cz Libraries are supposed to be really BIG & full of many different Books
    )
    set(TN ${Tool_Name}
        # This file shall use this ABBREVIATION
        # Please don't confuse this with "Target_Name"
        # TN = Tool_Name
        # List of Variables Created [all shall be here]
            # REY_SCOUT_${TN}_PATHS   ---> Basically where to "Find" yk
            # REY_FETCH_${TN}_BASE_DIR
            # REY_FOUND_${TN}_LIBRARY ---> CACHED String to where ${Binary_Names} is located
            # REY_FOUND_${TN}_INCLUDE ---> CACHED String to where ${Header_Name}  is located
    )
    if(  (NOT DEFINED REY_FETCH_${TN}_BASE_DIR)   OR   ("${REY_FETCH_${TN}_BASE_DIR}" STREQUAL "")  )

        set(REY_FETCH_${TN}_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
            # Won't be USED if ${Git_SubModule} is defined & non-empty string
    endif()
        set(REY_SCOUT_${TN}_PATHS)
# --------------------

# All the Variables above.... You are supposed to modify as per different Libraries
# Pseudocode for this file
# --------------------
    # if (REY_SCOUT_${TN}_PATHS != "")
        # find_library(${Binary_Names})
        # find_path(${TN}/${Header_Name})
        # USE:- REY_SCOUT_${TN}_PATHS
        # Check FOUND / LOG FATAL ERROR
        
    # elseif(  (DEFINED Git_SubModule)   AND   (NOT "${Git_SubModule}" STREQUAL "")  )
        # git submodule init / update
            
    # else()
        # if(NOT EXISTS ${REY_FETCH_${TN}_BASE_DIR}/${Git_Name} )
            # git clone ${Git_Link}
            # add_subdirectory(${Git_Name})
        # else()
            # if(NOT EXISTS ${Git_CheckFiles})
                # LOG FATAL ERROR
            # else()
                # add_subdirectory(${Git_Name})
            # endif()
        # endif()
    # endif()
# --------------------






























# --------------------
    if(NOT DEFINED ${CMAKE_BUILD_TYPE})
        set(CMAKE_BUILD_TYPE Debug)
    endif()
# --------------------
if (  (DEFINED REY_SCOUT_${TN}_PATHS)   AND   (NOT "${REY_SCOUT_${TN}_PATHS}" STREQUAL "")  )
    # ================================ FINDING ${Binary_Names} =================================
        find_library(tmp_scout_${TN}_lib
            NAMES
                ${Binary_Names}
            DOC
                ""
            PATHS
                ${REY_SCOUT_${TN}_PATHS}
            PATH_SUFFIXES
                Debug
                Release
                Lib         # Windows
                lib         # UNIX/MAC
                libs
                extern-libs

            NO_CACHE
            #NO_DEFAULT_PATH
        )

        if (EXISTS ${tmp_scout_${TN}_lib})
            set(  
                REY_FOUND_${TN}_LIBRARY
                ${tmp_scout_${TN}_lib}
                CACHE STRING "" FORCE
            )
            message(STATUS "[REY_FetchV3_${TN}]")
            message(STATUS "    Found 1 File:- ${tmp_scout_${TN}_lib}")
        endif()
    # ================================ FINDING ${Binary_Names} =================================


    # ================================ FINDING ${Header_Name} =================================
        find_path(tmp_scout_${TN}_inc
            NAMES
                ${Header_Name}
            PATHS
                ${REY_SCOUT_${TN}_PATHS}
            PATH_SUFFIXES
                ${TN}
                ${TN}/include
                ${TN}/include/${TN}
                include/${TN}
                include/include/${TN}
                includes/${TN}
                includes/include/${TN}
                extern-includes/${TN}
                extern-includes/include/${TN}

            NO_CACHE
        )

        if (tmp_scout_${TN}_inc)
            set(
                REY_FOUND_${TN}_INCLUDE
                ${tmp_scout_${TN}_inc}
                CACHE STRING "" FORCE
            )
            message(STATUS "[REY_FetchV3_${TN}]")
            message(STATUS "    Found include dir: ${tmp_scout_${TN}_inc}")
        endif()
    # ================================ FINDING ${Header_Name} =================================


    # =============================== if BOTH ARE FOUND =================================
        if (REY_SCOUT_${TN}_LIB AND REY_SCOUT_${TN}_INCLUDE)
            #         see Target_Name
            add_library(
                ${Target_Name} STATIC 
                IMPORTED
            )
            set_target_properties(
                ${Target_Name} 
                PROPERTIES
                    IMPORTED_LOCATION ${REY_SCOUT_${TN}_LIB}
                    INTERFACE_INCLUDE_DIRECTORIES ${REY_SCOUT_${TN}_INCLUDE}
            )
            message(STATUS "[REY_FetchV3_${TN}]")
            message(STATUS "    Created imported target ${Target_Name}")
            message(STATUS "    [cached] REY_FOUND_${TN}_LIB:-    ${REY_FOUND_${TN}_LIB}")
            message(STATUS "    [cached] REY_FOUND_${TN}_INCLUDE: ${REY_FOUND_${TN}_INCLUDE}")
        else ()
            message(STATUS "REY_SCOUT_${TN}_PATHS:- ${REY_SCOUT_${TN}_PATHS}")
            message(STATUS "tmp_scout_${TN}_lib:---   ${tmp_scout_${TN}_lib}")
            message(STATUS "tmp_scout_${TN}_inc:---   ${tmp_scout_${TN}_inc}")
            message(FATAL_ERROR "REY_SCOUT_${TN}_PATHS is defined but Could not find ${TN} library. 
                                Please Undefine it or make it EMPTY-STRING, if you want us to automatically `git clone ${Git_Link}`")
        endif()
    # =============================== if BOTH ARE FOUND =================================



elseif(  (DEFINED Git_SubModule)   AND   (NOT "${Git_SubModule}" STREQUAL "")  )


        message(STATUS "UPDATING SUBMODULE ${REY_FETCH_${TN}_BASE_DIR}/${Git_Name}")
        message(STATUS "Download Progress logged inside ${REY_FETCH_${TN}_BASE_DIR}/${TN}_Download_stdout.log ")
    execute_process(
        COMMAND             git submodule init
        COMMAND             git submodule update
        WORKING_DIRECTORY ${Git_SubModule}

        TIMEOUT 10              # seconds
        COMMAND_ECHO STDOUT     # output's the part after "COMMAND" few lines above
    )
        message(STATUS "Updating Done")

        add_subdirectory(${Git_SubModule})    #Output:- ${Target_Name}


else()



    if( (NOT EXISTS ${REY_FETCH_${TN}_BASE_DIR}/${Git_Name}) )
        message(STATUS "Fetching ${Git_Link}"   "inside ${REY_FETCH_${TN}_BASE_DIR}")
        message(STATUS "Download Progress logged inside ${REY_FETCH_${TN}_BASE_DIR}/${TN}_Download_stdout.log ")

            execute_process(
                #COMMAND cmd /c "git clone --progress ${Git_Link} > ${TN}_Download.log 2>&1"
                COMMAND          git clone --progress ${Git_Link}

                #COMMAND        "git clone --progress https://github.com/fmtlib/fmt"
                # With Quotation marks, it doesn't redirect stdout to OUTPUT_FILE/VARIABLE

                WORKING_DIRECTORY ${REY_FETCH_${TN}_BASE_DIR}

                OUTPUT_VARIABLE tmp_stdout               ERROR_VARIABLE tmp_stdout
                # OUTPUT_FILE     fmt_Download_stdout.log  ERROR_FILE     fmt_Download_stdout.log
                # Both doesn't work @ the same time

                TIMEOUT 10              # seconds
                COMMAND_ECHO STDOUT     # output's the part after "COMMAND" few lines above
            )

        file(WRITE "${REY_FETCH_${TN}_BASE_DIR}/${TN}_Download_stdout.log" "${tmp_stdout}\n")
        message(STATUS "tmp_stdout:- ${tmp_stdout}")
        message(STATUS "Fetching Done")


        add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_Name})    #Output:- ${Target_Name}
    else()
        set(GitHub_FILES_isOK TRUE)
        foreach(file_x ${Git_CheckFiles})
            if(NOT EXISTS "${REY_FETCH_${TN}_BASE_DIR}/${file_x}")
                set(GitHub_FILES_isOK FALSE)

                message(STATUS "[REY_FetchV3_${TN}]")
                message(STATUS "     REY_FETCH_${TN}_BASE_DIR:- ${REY_FETCH_${TN}_BASE_DIR}")
                message(STATUS "dA = REY_FETCH_${TN}_BASE_DIR/${Git_Name} ----> EXISTS")
                message(STATUS "             Git_CheckFiles --> ${file_x} ----> DOESN't EXIST")
                message(STATUS "                                     ")
                message(STATUS "As Long as 'dA' exists ---> `git clone ${Git_Link}` won't work")

                message(FATAL_ERROR "ERROR INFO Has been Logged above\n
                                    ERROR:- REY_FETCH_${TN}_BASE_DIR/${Git_Name} exists, but it's not a proper GIT CLONE\n
                                    see .REY_FetchV3.cmake TOP Documentation part for INPUT-Settings/Variables")
            endif()
        endforeach()
        add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_Name})    #Output:- ${Target_Name}
    endif()



endif()