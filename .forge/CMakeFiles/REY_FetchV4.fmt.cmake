# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.fmt.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (${REY_FetchV4_MODS_PATH} NOT STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.fmt.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.fmt.cmake)
    endif()
endif()

#        |- fmt uses these:-
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/.install CACHE PATH "" FORCE)
    set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/extern-libs  CACHE PATH "" FORCE)
    # [If you change above stuffs]:- RERUN:- FRESH CONFIGURATION, BUILD, INSTALL

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X_RESET.cmake)