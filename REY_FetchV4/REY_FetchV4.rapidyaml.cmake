# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X_RESET.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.rapidyaml.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (NOT "${REY_FetchV4_MODS_PATH}" STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.rapidyaml.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.rapidyaml.cmake)
    endif()
endif()




# |---------------- rapidyaml specific CMAKE settings ----------------|
    option(RYML_INSTALL "" OFF)
    # SET(RYML_INSTALL OFF CACHE BOOL "Use some expat option")

    if(WIN32)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")          # if clang-MSVC-toolchain
            add_compile_definitions(C4_MSVC)
            add_compile_options(-DC4_MSVC)                  # This two did not work globally TwT....

            if(NOT (CMAKE_CXX_FLAGS MATCHES "-DC4_MSVC"))   # if STRING matches REG-EX

                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DC4_MSVC"  CACHE STRING "CMAKE_CXX_FLAGS" FORCE)
                message(STATUS "[REY_FetchV4.rapidyaml.cmake] Added -DC4_MSVC to CMAKE_CXX_FLAGS")
                    # Gotta set the compile definitions in CMAKE GLOBAL SCOPE
                    # like for everything even outside of current cmake project
                    # Because, Everything that's gonna #include ryml stuffs, is gonna need this DEFINITION

            else()

                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}"            CACHE STRING "CMAKE_CXX_FLAGS" FORCE)
                message(STATUS "[REY_FetchV4.rapidyaml.cmake]       -DC4_MSVC     already exists")

            endif()

            message(STATUS "[REY_FetchV4.rapidyaml.cmake] Cache Variable -> CMAKE_CXX_FLAGS:- " ${CMAKE_CXX_FLAGS})
        endif()
    endif()
# |---------------- rapidyaml specific CMAKE settings ----------------|


# TODO: Try Creating a DUMMY Target & target_compile_definitions(DUMMY_RYML_REY_TARGET PUBLIC C4_MSVC)




include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)





#[[
# |---------------- CleanUp - rapidyaml specific CMAKE settings ----------------|
    if(WIN32) # Check if the platform is Windows
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # Check if the compiler is Clang
            remove_definitions(-DC4_MSVC) # Define the C4_MSVC macro
        endif()
    endif()
# |---------------- CleanUp - rapidyaml specific CMAKE settings ----------------|
]]