# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
    set(Tool_Name)
    set(TN)

    # Way-1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
    set(REY_SCOUT_${TN}_PATHS)
    set(Binary_Hints)
    set(Header_Name)
    set(Target_Name)

    # Way-2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty]
    set(Git_SubModule)

    # Way-3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
    set(Zip_Links 
        "https://github.com/REYNEP/libs-win32/raw/main/breakpad.zip"   "${CMAKE_CURRENT_SOURCE_DIR}/.forge/lib"     "breakpad-win32.zip"
        "https://github.com/REYNEP/libs-include/raw/main/breakpad.zip" "${CMAKE_CURRENT_SOURCE_DIR}/.forge/include" "breakpad-inc.zip"
        # LINK    path/to/save     name.zip
                # path must exist
    )

    # Way-4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
    set(REY_FETCH_${TN}_BASE_DIR)
    set(Git_Link)
    set(Git_CloneDir_Name)
    set(Git_Clone_Recursive OFF)
    set(Git_CheckFiles)
# --------------------