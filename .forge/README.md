# 📔 Why `.forge`?
### 1. What is `.forge`?
- it's just like `build` / `build-x64` / `.build` folders
- but with some extra ideas 😜
### 2. When will you need this?
- Answer:- *When you wanna do more than just `build` inside `build`-dir 💁‍♀️*
### 3. Why is this important?
- To keep stuffs ORGANIZED
### 4. Why yet another differnet name for the same old `build` directory?
- To keep more stuffs inside
- we can download external stuffs inside this folder, instead of doing it outside of the Source/Root directory 
    - [which is what big project usually does]
- we can have `.forge/build` or `.forge/build-cmake` all different types of thingies. They don't have to be @ Source/Root directory
### 5. Why should YOU use this concept?
- When you don't wanna clutter the Source/Root directory of your Library/Program
### 6. How does this work?
- *Well, the Draft/First-Proposal is below*

# 📜 Draft - Second Proposal
```py
.repo
    |- .forge
        |- .build-x64
        |- .build_CMAKE = CMake Configuration & Building. VSCODE Settings:- "cmake.buildDirectory"

        |- include = external library stuffs
        |- lib = external library stuffs [probably zips that got downloaded/unzipped]

        |- <ext-lib> = maybe a cloned / submodule external library
                     = also maybe, you used REY_FetchV4 to Grab it 😊
```

<div style="page-break-after: always;"></div>

# 🛠️ Draft - First Proposal for .forge directory
```py
.repo
    |- .forge
        |- .build_CMAKE = CMake Configuration & Building. VSCODE Settings:- "cmake.buildDirectory"

        |- .CMakeFiles = Stuff that CMakeLists.txt needs/includes

        |- .libs_CMAKE_FETCH = external libraries that need to be built PER_OS/PLATFORM
            |- fmt:- https://github.com/fmtlib/fmt

        |- .libs_GIT    = alternative to CMAKE_FETCH. i.e. Manually Building 😵‍💫 [EMPTY FOR NOW]
        |- .libs_REYMOD = alternative to CMAKE_FETCH.
            |- include  = GIT_REPO
                |- Vulkan-Headers
            |- linux    = GIT_REPO
            |- osX      = GIT_REPO
            |- win32    = GIT_REPO
                |- vulkan-1.lib
                These 4 above are Separate GIT_REPOs that I plan on to maintain
                These 4 above will be downloaded by CMAKE_FETCH during CONFIGURATION
                These 4 above won't be available to be grabbed by GIT_SUBMODULE
            |
            |- Why Separate from `libs_CMAKE_FETCH`?
                |- Stuff that "I Don't have to build". e.g. vulkan. LunarG Builds & serves that instead.
                |- CUSTOM_MODIFIED_Libraries would be here.
                |- Libraries with HUGE_DOWNLOAD size, I cut them & keep short stuff here.
                    |- Vulkan-Headers Repository = 50-70 MB GitHub download.
                        I turned it into basically    ~1 MB ZIP

        |- .sandbox_libs_EXT = My SandBox for playing around with libraries 😵‍💫 [EMPTY FOR NOW]
```

### Possible name changes of .build_n_libs_EXT:-
    .rescources .hub .vault .forge .matrix .citadel .arc .realm 
    .depot .junction .portal .gateway .conduit
    .passage .doorway