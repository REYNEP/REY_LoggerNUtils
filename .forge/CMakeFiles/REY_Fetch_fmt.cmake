# --------------------
#  INPUT Options:- 
#       ${REY_FETCH_FMT_BASE_DIR} ---> Stuff will be fetched into this DIR
# OUTPUT Options:- 
#       ${fmt::fmt} ---------> this is a "Target"
#                              this is How you use it:-
#                                   target_link_libraries(idk fmt::fmt)
#                                   target_include_directories(idk PUBLIC fmt::fmt)
# --------------------

# --------------------
    if(NOT DEFINED ${CMAKE_BUILD_TYPE})
        set(CMAKE_BUILD_TYPE Debug)
    endif()
# --------------------
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${REY_FETCH_FMT_BASE_DIR})
set(FETCHCONTENT_QUIET TRUE)        # Doesn't have any effect on "GIT_PROGRESS" / "LOG_DOWNLOAD"

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        e3ddede6c4ee818825c4e5a6dfa1d384860c27d9     # "fmt" Version:- 11.1.1
        GIT_PROGRESS   TRUE         # ON:- logs DOWNLOAD_PROGRESS into `LOG_DIR`

        LOG_DIR      ${REY_FETCH_FMT_BASE_DIR}
        LOG_DOWNLOAD   TRUE
        LOG_UPDATE     TRUE
        LOG_PATCH      TRUE
        LOG_CONFIGURE  TRUE
        LOG_BUILD      TRUE
        LOG_INSTALL    TRUE
        LOG_TEST       TRUE
        LOG_MERGED_STDOUTERR TRUE
        #More Options:- https://cmake.org/cmake/help/latest/module/ExternalProject.html
        #Quote:-
        #   "The <contentOptions> can be any of the download, update, or patch options that the ExternalProject_Add() command understands."
    )

message(STATUS "Fetching github.com/fmtlib/fmt inside ${FETCHCONTENT_BASE_DIR}")
message(STATUS "Download Progress being logged inside ${FETCHCONTENT_BASE_DIR}")
    FetchContent_MakeAvailable(fmt)
message(STATUS "Fetching Done")