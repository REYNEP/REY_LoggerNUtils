```py
0. REY_FetchV4 --> Mix of it all below
    +5:- Use Github to keep track of LIBS & Include Versions
         https://github.com/REYNEP/libs-win32
         https://github.com/REYNEP/libs-include

1. How Blender Does it --> 4/10
    -1:- Libs & Include has to be Manually Updated.

2. CMAKE FETCH --> 7/10
    -1:- Download Progress is shown by taking up so many lines, like hundreds.
    -2:- Can't Fetch SPECIFIC Folder/SubDirectory from a repo from GITHUB

3. Python Script to Download --> 5/10
4. GIT SubModule --> 4/10
5. Maintaining a .zip in GDrive --> 2/10
6. Just supplying all the external library binaries along with the project souurce --> 1/10
```

### My Approach to External Libraries:- `CMAKE_FETCH` + Blender's Approach
    1. CMAKE_FETCH most stuffs ----> like fmt
    2. .libs_REYMOD = Libraries CUT/Stripped/Modified by REYNEP ----> like vulkan
        Supplying these like Blender supplies their External Libraries

    3. Even the stuff inside .libs_REYMOD would be fetches by CMAKE 😜

## Draft - First Proposal for .forge directory
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