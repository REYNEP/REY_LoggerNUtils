#pragma once
#include "REY_Logger.hh"
#include "REY_Types.hh"

#ifdef REY_STD_WRAP_IMPLIMENTATION

    /**
     * Summary of this file
     * 
     * 1. I didn't wanna include sooooo many STANDARD Library Headers in every single file of mine.
     *      --> REY_malloc()
     *      --> REY_memcpy()
     *      --> REY_strlen()
     * 
     */
    #include "stdlib.h"
    void  *REY_malloc(size_t bytes) {
        return malloc(bytes);
    }

    #include "string.h"
    void  *REY_memcpy(void *to, void *from, size_t bytes) {
        return memcpy(to, from, bytes);
    }
    size_t REY_strlen(const char *str) {
        return strlen(str);
    }

    /**
     * Summary of this file
     * 
     * 2. MSVC-Clang-Toolchain -> strcpy() is deprecated -> use: strcpy_s
     *      --> REY_strcpy_s()    [Long Implementation] [not suggested to use]
     *      --> REY_strcpy()      [use this one iguess] [😜]
     */
    #include "string.h"
    char* REY_strcpy(const char *from) {
        char  *to = new char[strlen(from) + 1];

            #ifdef _MSC_VER
                strcpy_s(to, strlen(from) + 1, from);
            #else
                strcpy(to, from);
                // On MSVC-Clang-Toolchain Clang complains that this function DEPRECATED
            #endif

        return to;
    }

#else

    /**
     * @param bytes:- How many bytes do you wanna Allocate on the Heap-Memory of RAM
     */
    void   *REY_malloc(size_t bytes);
    void   *REY_memcpy(void *to, void *from, size_t bytes);
    size_t  REY_strlen(const char *str);
    /**
     * @param to_bytes_max:- Should be one 1 more than "letterCount(word)"
     * @param to:- copies the null-terminator "\0" too 💁‍♀️
     * 
     * I don't suggest using this function. strcpy_s "Asserts". it kinda annoys me 😶‍🌫️
     * I       suggest using the  function below
     */
    void REY_strcpy_s(char *to, rsize_t to_bytes_max, const char *from);
    /**
     * @param from
     * @returns [char *to]
     *    - [delete/free by yourself, when you need to]
     */
    char *REY_strcpy(const char *from);

#endif