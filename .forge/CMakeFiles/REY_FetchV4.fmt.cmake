# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.fmt.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (${REY_FetchV4_MODS_PATH} NOT STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.fmt.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.fmt.cmake)
    endif()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)