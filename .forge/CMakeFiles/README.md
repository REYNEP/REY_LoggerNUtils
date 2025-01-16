```cmake
# Problem:- Authors that are gonna use "REY_LoggerNUtils" will need to modify variables inside ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"
#           But How can they? That file is inside REYNEP's "REY_LoggerNUtils" Repo.

# Solution-1 [HECTIC]
#     the variables from inside of ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"
#     Authors can just set those themselves before add_subdirectory(REY_LoggerNUtils)
#         HECTIC ISSUE:- after add_subdirector(REY_LoggerNUtils) is done ---> Authors also need to RESET Those Variables to EMPTY

# Solution-2 [HECTIC]
#     have a variable inside REY_LoggerNUtils/CMakeLists.txt to control PRIORITY_BASED_LOCATION for ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"
#     like authors that are gonna use REY_LoggerNUtils, having the modified copy of ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"
#          and then they are directing REY_LoggerNUtils/CMakeLists.txt to include their MODIFIED COPY
#
#           HECTIC ISSUE:- But this would mean that REY_Fetch can't ever be like a PACKAGE Manager itself....

# Solution-3 [WORKS & Feels like a Package Manager]
# The Idea is:- REY_LoggerNUtils/CMakeLists.txt includes ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"

# Now, obviously any library that uses REY_LoggerNUtils, can't modify   REY_LoggerNUtils/CMakeLists.txt
#     +obviously any library that uses REY_LoggerNUtils, can't modify ".forge/CMakeFiles/REY_FetchV3_fmt.cmake"

# 1. Having multiple copies of ".forge/CMakeFiles/REY_FetchV3_fmt.cmake" felt dumb
# 2. 
```




## V4
1. `REY_FetchV4.cmake`:- The Goddamn Main file, where all the work happens
2. `REY_FetchV4_X.<lib-name>.cmake`:- "X" = variables 😃
3. `REY_FetchV4_MOD.<lib-name>.cmake`:- imagine B uses A. C uses B. C also directly uses A. C wants to control how B fetches A. 
    - C should have a copy of this file & SET `REY_FetchV4_MODS_PATH`
4. `REY_FetchV4.<lib-name>.cmake`:- includes the above two thingies
    - Here in These files ---> We can do Library Specific Extra Stuffs
5. `REY_FetchV4_X_Reset.cmake`:- RESETs the Variables back to EMPTY-STRING