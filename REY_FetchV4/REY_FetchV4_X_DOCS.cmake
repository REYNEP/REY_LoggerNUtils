# --------------------
    set(Git_Link "https://github.com/fmtlib/fmt")
    set(Git_CloneDir_Name fmt
        # git clone <link> ----> auto creates a Directory. This variable should store that name
    )
    set(Git_SubModule
        # ex1:- ${CMAKE_CURRENT_SOURCE_DIR}/${Git_CloneDir_Name}
        # Should be a FULL PATH
            # We will assume that this path ---> Exists
            # If this is not  EMPTY-STRINGS ---> THIS WILL BE USED
            #                              |---> ${REY_FETCH_${TN}_BASE_DIR} won't be used
    )
    set(Git_CheckFiles
          ${Git_CloneDir_Name}/CMakeLists.txt
          ${Git_CloneDir_Name}/src/fmt.cc
        # ${Git_CloneDir_Name}/REY_Logger.cpp

        # ${Git_CloneDir_Name}/src/fmt.cc
        # ${Git_CloneDir_Name} folder itself is inside ${REY_FETCH_${TN}_BASE_DIR} --> We will handle that part
    )
    set(Binary_Hints
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
#       1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
#       2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty]
#       3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
#       4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
#
# OUTPUT Options:- 
#       ${REY_FOUND_${TN}_LIBRARY}  ---> CACHED String to where ${Binary_Hints} is located
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
            # REY_FOUND_${TN}_LIBRARY ---> CACHED String to where ${Binary_Hints} is located
            # REY_FOUND_${TN}_INCLUDE ---> CACHED String to where ${Header_Name}  is located
    )
    set(REY_SCOUT_${TN}_PATHS)
    set(REY_FETCH_${TN}_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
        # Won't be USED if ${Git_SubModule} is defined & non-empty string
    set(Zip_Links 
        # "https://github.com/REYNEP/libs-win32/raw/main/breakpad.zip"   "${REY_FETCH_${TN}_BASE_DIR}/lib"     "breakpad-win32.zip"
        # "https://github.com/REYNEP/libs-include/raw/main/breakpad.zip" "${REY_FETCH_${TN}_BASE_DIR}/include" "breakpad-inc.zip"
        #  LINK    path/to/save     name.zip
                # path must exist
    )
# --------------------