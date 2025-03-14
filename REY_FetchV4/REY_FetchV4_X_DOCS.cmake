# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
# --------------------
#
#  INPUT Options:-
#       All the things above & below before Pseudocode
#     Variations:-
#       1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
#       2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty][Already Done:- `git submodule add <link> path/to/folder`]
#       3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
#       4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
#
# OUTPUT Options:-
#       [Way-1] ${REY_FOUND_${TN}_LIBRARY}  ---> CACHED String to where ${Binary_Hints} is located
#       [Way-1] ${REY_FOUND_${TN}_INCLUDE}  ---> CACHED String to where ${Header_Name}  is located
#       [Way-1] add_library(${Target_Name}) ---> ${Target_Name} is an option below 
#
# --------------------
    set(Tool_Name           # usually i set this ==> into this file's name `REY_FetchV4_X.vulkan.cmake` 😊
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




#    _  _    __          __               __ 
#  _| || |_  \ \        / /              /_ |
# |_  __  _|  \ \  /\  / /_ _ _   _ ______| |
#  _| || |_    \ \/  \/ / _` | | | |______| |
# |_  __  _|    \  /\  / (_| | |_| |      | |
#   |_||_|       \/  \/ \__,_|\__, |      |_|
#                              __/ |         
#                             |___/          
    # Way-1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
    set(REY_SCOUT_${TN}_PATHS)
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


#    _  _    __          __              ___  
#  _| || |_  \ \        / /             |__ \ 
# |_  __  _|  \ \  /\  / /_ _ _   _ ______ ) |
#  _| || |_    \ \/  \/ / _` | | | |______/ / 
# |_  __  _|    \  /\  / (_| | |_| |     / /_ 
#   |_||_|       \/  \/ \__,_|\__, |    |____|
#                              __/ |          
#                             |___/           
    set(Git_SubModule
        # ex1:- ${CMAKE_CURRENT_SOURCE_DIR}/${Git_CloneDir_Name}
        # Should be a FULL PATH
            # We will assume that this path ---> Exists
            # We will assume that this path ---> you already added this submodule to your project using:-
            #                                           `git submodule add <link> path/to/folder`
            # If this is not  EMPTY-STRINGS ---> THIS WILL BE USED
            #                              |---> ${REY_FETCH_${TN}_BASE_DIR} won't be used
    )


#    _  _    __          __               ____  
#  _| || |_  \ \        / /              |___ \ 
# |_  __  _|  \ \  /\  / /_ _ _   _ ______ __) |
#  _| || |_    \ \/  \/ / _` | | | |______|__ < 
# |_  __  _|    \  /\  / (_| | |_| |      ___) |
#   |_||_|       \/  \/ \__,_|\__, |     |____/ 
#                              __/ |            
#                             |___/             
    set(Zip_Links 
        # "https://github.com/REYNEP/libs-win32/raw/main/breakpad.zip"   "${REY_FETCH_${TN}_BASE_DIR}/lib"     "breakpad-win32.zip"
        # "https://github.com/REYNEP/libs-include/raw/main/breakpad.zip" "${REY_FETCH_${TN}_BASE_DIR}/include" "breakpad-inc.zip"
        #  LINK    path/to/save     name.zip
                # path must exist
    )



#    _  _    __          __                _  _   
#  _| || |_  \ \        / /               | || |  
# |_  __  _|  \ \  /\  / /_ _ _   _ ______| || |_ 
#  _| || |_    \ \/  \/ / _` | | | |______|__   _|
# |_  __  _|    \  /\  / (_| | |_| |         | |  
#   |_||_|       \/  \/ \__,_|\__, |         |_|  
#                              __/ |              
#                             |___/               
    set(REY_FETCH_${TN}_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
        # Won't be USED if ${Git_SubModule} is defined & non-empty string
    set(Git_Link "https://github.com/fmtlib/fmt")
    set(Git_CloneDir_Name fmt
        # git clone <link> ----> auto creates a Directory. This variable should store that name
    )
    set(Git_Clone_Recursive OFF)
        # git clone --recursive https://github.com/biojppm/rapidyaml
    set(Git_CheckFiles
          ${Git_CloneDir_Name}/CMakeLists.txt
          ${Git_CloneDir_Name}/src/fmt.cc
        # ${Git_CloneDir_Name}/REY_Logger.cpp

        # ${Git_CloneDir_Name}/src/fmt.cc
        # ${Git_CloneDir_Name} folder itself is inside ${REY_FETCH_${TN}_BASE_DIR} --> We will handle that part
    )
# --------------------