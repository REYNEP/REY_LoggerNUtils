#pragma once

#ifdef _WIN32
    #define REY_TYPES_use_custom_definitions
#endif

#ifdef _MSC_VER
    #define REY_TYPES_use_custom_definitions
#endif

// Detect Clang with MSVC toolchain
#if defined(__clang__) && defined(_MSC_VER)
    #define REY_TYPES_use_custom_definitions
#endif

#ifdef REY_TYPES_use_custom_definitions
    /** These are all Windows 11 64bit definitions, But should work on any other 64bit OS too */
    typedef signed char        int8_t;
    typedef short              int16_t;
    typedef int                int32_t;
    typedef long long          int64_t;
    typedef unsigned char      uint8_t;
    typedef unsigned short     uint16_t;
    typedef unsigned int       uint32_t;
    typedef unsigned long long uint64_t;

    // Definitions of common types
    #ifdef _WIN64
        typedef unsigned __int64 size_t;
        typedef __int64          ptrdiff_t;
        typedef __int64          intptr_t;
    #else
        typedef unsigned int     size_t;
        typedef int              ptrdiff_t;
        typedef int              intptr_t;
    #endif

    typedef size_t rsize_t;

    //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //
    // Basic Types
    //
    //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    typedef int                           errno_t;
    typedef unsigned short                wint_t;
    typedef unsigned short                wctype_t;
    typedef long                          __time32_t;
    typedef __int64                       __time64_t;
#else
    #include <stdint.h>
    #include <stddef.h>
#endif