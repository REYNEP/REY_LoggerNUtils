# REY_LoggerNUtils `V0.1`
- `V0.1beta`:- https://gist.github.com/REYNEP/14a628ab270cae461a926ba212226492


### Example
```cpp
#include "REY_Logger.hh"
#include <fmt/core.h>
// CMAKE CONFIGURE ---> will automatically FETCH / BUILD / LINK / INCLUDE_PATH of fmt
// just use `target_link_libraries(<your_target_name> amVK_LoggerNUtils)` in CMAKE 
//      & you also got access to fmt

int main(void) {
    amVK_LOG("Hello, World!");
    fmt::print("Hello, World!\n");
    return 0;
}
```


## Building / Using [SUMMARY]
1. `fmt`:- automatically **"FETCHED"** --> Built --> Linked by CMAKE
2. `target_link_libraries(<your_target_name> amVK_LoggerNUtils)`
3. So it's basically automatically handled 😉
4. `.forge`:- `lib-REY_LoggerNUtils.lib` will be INSTALLED here
    - `fmt` will be fetched here & installed here


</br>
</br>
</br>
</br>

## OLD Notes [will be refactored later]:
- No `#include <cstdlib>` or `#include <iostream>`  such thing is done in the headers
    - all `include` was done inside `amVK_LOGGER/UTILS_IMPLIMENTATION` sections.... [which are supposed to end up in 1 single .cpp TRANSLATION UNIT]
    </br>
- we made a wrapper around STANDARD LIB `malloc` & `memcpy` (`amVK_malloc` & `amVK_memcpy`)
    - cz, `amVK_Utils::merge_sort` is still template based....
    - also `amVK_memcpy` is used in `amVK_ArrayDYN<T>::resize` 
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

## External Libraries [`.forge`]
1. `fmt`:- Official Git:- https://github.com/fmtlib/fmt
    - What is it?  :- https://github.com/fmtlib/fmt?tab=readme-ov-file#examples
    - CMake / Using:- https://fmt.dev/11.1/get-started/
    - CheatSheet / Code Examples:- https://hackingcpp.com/cpp/libs/fmt.html

2. `.forge` folder is an idea
    - I store/fetch/modify/custom-build External Libraries in here
    - For the whole idea, check:- idk https://github.com/REYNEP/idk/tree/33da809ede9e6ecc4f1a9d2c7c222ca27acff013




## Building / Using [Full Explanation]
1. `fmt`:- automatically **"FETCHED"** by `CMAKE` ----> Built & **"PUBLIC"** Linked too
    - **"PUBLIC"** Linked:- You can use `fmt` directly (e.g. `<fmt/core.hh>`) if you do:-
        - `target_link_libraries(<target_name> amVK_LoggerNUtils)`

```py
# --------------------
# OUTPUT Options:- 
#       Library Name:- amVK_LoggerNUtils
#              Usage:- target_link_libraries(<target_name> amVK_LoggerNUtils)
#
# Possible Untested Output Options:- [Might Not Work, cz of SCOPE Limitations]
#       ${fmt::fmt} ---------> this is a "Target"
#                              this is How you use it:-
#                                   target_link_libraries(idk fmt::fmt)
#                                   target_include_directories(idk PUBLIC fmt::fmt)
# --------------------
```