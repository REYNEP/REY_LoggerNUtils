# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X_RESET.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.libcs50.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (NOT "${REY_FetchV4_MODS_PATH}" STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.libcs50.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.libcs50.cmake)
    endif()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)






set (cs50_CLONE_DIR ${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name})

# ---------------- download CMakeLists.txt ----------------
if(NOT EXISTS "${cs50_CLONE_DIR}/CMakeLists.txt")
    message(STATUS "📦 Starting download: github.com/REYNEP/libcs50/CMakeLists.txt")

    file(DOWNLOAD
        "https://github.com/REYNEP/libcs50/raw/refs/heads/main/CMakeLists.txt"
        "${cs50_CLONE_DIR}/CMakeLists.txt"
        SHOW_PROGRESS
        STATUS download_status
    )

    list(GET download_status 0 status_code)
    list(GET download_status 1 status_string)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "❌ File download failed (CMakeLists.txt): ${status_string}")
    endif()

    message(STATUS "✅ Successfully downloaded: CMakeLists.txt")
else()
    message(STATUS "📁 Already exists: CMakeLists.txt — skipping download")
endif()
# ---------------- download CMakeLists.txt ----------------

# ---------------- download cs50.h with support for C++ ----------------
if(NOT EXISTS "${cs50_CLONE_DIR}/src/rey_cs50.h")
    message(STATUS "📦 Starting download: github.com/REYNEP/libcs50/src/cs50.h")

    file(DOWNLOAD
        "https://github.com/REYNEP/libcs50/raw/refs/heads/main/src/cs50.h"
        "${cs50_CLONE_DIR}/src/rey_cs50.h"
        SHOW_PROGRESS
        STATUS download_status
    )

    list(GET download_status 0 status_code)
    list(GET download_status 1 status_string)

    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "❌ File download failed (cs50.h): ${status_string}")
    else()

        message(STATUS "✅ Successfully downloaded: cs50.h")

        file(RENAME 
            "${cs50_CLONE_DIR}/src/cs50.h" 
            "${cs50_CLONE_DIR}/src/cs50_og.h" 
        )

        file(COPY "${cs50_CLONE_DIR}/src/rey_cs50.h"
             DESTINATION "${cs50_CLONE_DIR}/")

        file(RENAME 
            "${cs50_CLONE_DIR}/rey_cs50.h" 
            "${cs50_CLONE_DIR}/src/cs50.h"
        )
            
    endif()
else()
    message(STATUS "📁 Already exists: cs50.h — skipping download")
endif()
# ---------------- download cs50.h with support for C++ ----------------











add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name})






#[[ Version 1

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cs50.CMakeLists.cmake 
    ${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name}/CMakeLists.txt 
        COPYONLY
)

add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name})

#]]