# REY_LoggerNUtils `V0.4`
- `V0.4`:- WIP
    - `REY_FetchV4`:- 1.Scout, 2.Submodule, 3.ZipLinks, 4.Clone/Fetch 😊 
    - WIP: StackTrace on Crash / Signal Handler / `google breakpad` + `boost stacktrace` + `StackWalker` + `google crashpad` + `sentry` + `raygun` + `BugSnag` + `RollBar`
- `V0.3`:- DONE
    - `.install`:- it's a Folder for `lib-REY_LoggerNUtils.lib` & "external libraries" installation
    - added `.forge/CMakeFiles/REY_FetchV2_fmt.cmake`
    - added `.forge/CMakeFiles/REY_FetchV3.cmake`
- `V0.2`:- Prefix_Tag:- 😢 REFACTORED ["amVK" --> "REY"]
- `V0.1`:- Initial Commit: moving from [GIST ---> GITHUB]
- `V0.1beta`:- https://gist.github.com/REYNEP/14a628ab270cae461a926ba212226492


### Example
```cpp
#include "REY_Logger.hh"
#include <fmt/core.h>
// CMAKE CONFIGURE ---> will automatically FETCH / BUILD / LINK / INCLUDE_PATH of fmt
// just use `target_link_libraries(<your_target_name> REY_LoggerNUtils)` in CMAKE 
//      & you also got access to fmt

int main(void) {
    REY_LOG("Hello, World!");
    fmt::print("Hello, World!\n");
    return 0;
}
```


## Building / Using [SUMMARY]
It's basically automatically handled 😉:-
```sh
git clone https://github.com/REYNEP/REY_LoggerNUtils <path>
# or 
git add submoule https://github.com/REYNEP/REY_LoggerNUtils <path>

# Way 1
# Open `REY_LoggerNUtils` in VSCODE
# F1 > CMake: Configure
# F1 > CMake: Build
# F1 > CMake: Install [Default Folder:- REY_LoggerNUtils/.install]

# You can optinally take a glimpse @ "REY_LoggerNUtils/CMakeLists.txt" 😜 
# for better understanding.... it's pretty small

# Way 2:- add these in your CMakeLists.txt
#      add_subdirectory( <path/to/REY_LoggerNUtils> )
# target_link_libraries( <your_target_name>  REY_LoggerNUtils )

# Way 3:- Meson & Premake Support [TBA]
# Way 4:- Ninja/MakeFiles + Python Downloader Script [TBA]
```

</br>
</br>
</br>
</br>

## External Libraries [`.forge`]
1. `fmt`:- automatically **"FETCHED"** --> Built --> **"PUBLIC"** Linked to `REY_LoggerNUtils` by CMAKE
    - **"PUBLIC"** Linked:- Will be available to you too:- 
        - i.e. You can `#include <fmt/core.h>`
        - & `fmt` will be automatically linked as you are linking `REY_LoggerNUtils` in CMAKE
    - Official Git:- https://github.com/fmtlib/fmt
    - What is it?  :- https://github.com/fmtlib/fmt?tab=readme-ov-file#examples
    - CMake / Using:- https://fmt.dev/11.1/get-started/
    - CheatSheet / Code Examples:- https://hackingcpp.com/cpp/libs/fmt.html

2. `.forge`:- `lib-REY_LoggerNUtils.lib` will be INSTALLED here
    - `fmt` will be fetched here & installed here
    - I store/fetch/modify/custom-build External Libraries in here
    - For the whole idea, check:- idk https://github.com/REYNEP/idk/tree/33da809ede9e6ecc4f1a9d2c7c222ca27acff013

3. `google breakpad`:- StackTracer on Crash Library. very hard to build on windows.
    - However I found a really cool & nice wiki & how-to about it
    - https://github.com/d1vanov/quentier/wiki/Building-and-installation-of-Quentier's-dependencies#building-google-breakpad
    - Took me Half an hour to find this guide & finally fkin build this shit
    - Building Google Breakpad on Windows:- THE GUIDE/WIKI Link Above
    - BREAKPAD vs CRASHPAD
        - https://stackoverflow.com/questions/52725299/what-is-the-difference-between-googles-breakpad-and-crashpad-libraries

```py
# --------------------
# OUTPUT Options:- 
#       Library Name:- REY_LoggerNUtils
#              Usage:- target_link_libraries(<target_name> REY_LoggerNUtils)
#
# Possible Untested Output Options:- [Might Not Work, cz of SCOPE Limitations]
#       ${fmt::fmt} ---------> this is a "Target"
#                              this is How you use it:-
#                                   target_link_libraries(idk fmt::fmt)
#                                   target_include_directories(idk PUBLIC fmt::fmt)
# --------------------
```

</br>
</br>
</br>
</br>


## OLD Notes [will be refactored later]:
- No `#include <cstdlib>` or `#include <iostream>`  such thing is done in the headers
    - all `include` was done inside `REY_Logger/UTILS_IMPLIMENTATION` sections.... [which are supposed to end up in 1 single .cpp TRANSLATION UNIT]
    </br>
- we made a wrapper around STANDARD LIB `malloc` & `memcpy` (`REY_malloc` & `REY_memcpy`)
    - cz, `REY_Utils::merge_sort` is still template based....
    - also `REY_memcpy` is used in `REY_ArrayDYN<T>::resize` 
    </br>
- our main goal was to make it light-weight.... even if you include these in thousands of files.... preprocessed files doesn't have too much weight
- officially this can be considered ***V0.1***
    - beta was the GIST:- https://gist.github.com/REYNEP/14a628ab270cae461a926ba212226492
- just clone this gist & use... + you won't need to care about the license... cz its....
    - LICENSE: BOOST LICENSE


</br>
</br>
</br>
</br>
</br>