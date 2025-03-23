# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
    set(Tool_Name taojson)
    set(TN ${Tool_Name})

    # Way-1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
    set(REY_SCOUT_${TN}_PATHS)
    set(Binary_Hints)
    set(Header_Name)
    set(Target_Name)

    # Way-2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty]
    set(Git_SubModule)

    # Way-3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
    set(Zip_Links)

    # Way-4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
    set(REY_FETCH_${TN}_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
    set(Git_Link "https://github.com/taocpp/json")
    set(Git_CloneDir_Name taojson)
    set(Git_Clone_Recursive ON)
    set(Git_CheckFiles
        ${Git_CloneDir_Name}/CMakeLists.txt
        ${Git_CloneDir_Name}/include/tao/json.hpp
    )
        # add_library(taocpp::json)
# --------------------