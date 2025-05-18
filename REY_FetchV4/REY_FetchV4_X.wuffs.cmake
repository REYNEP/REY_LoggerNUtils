# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
    set(Tool_Name wuffs)
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
    set(REY_FETCH_${TN}_BASE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
    set(Git_Link)
    set(Git_CloneDir_Name)
    set(Git_Clone_Recursive OFF)
    set(Git_CheckFiles)
    set(Git_AddSubdirectory OFF)

    # Way-5. Download Single Header/.cpp file based library
    set(SingleFile_Link https://raw.githubusercontent.com/google/wuffs/7250990196ab0306f16b639feefbbca4d5323080/release/c/wuffs-v0.4.c)
    set(SingleFile_Name wuffs-v0.4.c)
    set(SingleFile_Dir ${CMAKE_CURRENT_SOURCE_DIR}/.forge/wuffs)
    set(SingleFile_InterfaceTarget REY_FetchV4_wuffs)
    set(SingleFile_ShowProgress OFF)
# --------------------