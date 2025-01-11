/**
 * HOW TO USE
 *   option-1:- Use CMAKE add_subdirectory(amVK_LoggerNUtils)
 *   option-2:- 
 *      1. define REY_LOGGER_IMPLEMENTATION in one of the TRANSLATION_UNITs
 *      2. `include(${amVK_LoggerNUtils}/REY_Fetch_fmk.cmake)` lib_fmt will be automatically fetched
 *      3. 
 *         target_link_libraries(<idk> fmt::fmt)
 *         target_include_directories(<idk> PUBLIC fmt::fmt)
 * 
 *              idk = TRANSLATION_UNIT that you defined REY_LOGGER_IMPLEMENTATION
 * 
 * 
 * This file should be fully independant of any amVK Headers
 *  - I also made it super light.... it calls no `#include`, but there's a MACRO: REY_LOGGER_IMPLEMENTATION now
 *  - #define REY_LOGGER_IMPLEMENTATION    [in one of the .cpp files]
 *
 * Preprocessor RESC-1:
 *    https://sourceforge.net/p/predef/wiki/OperatingSystems/
 * MSVC Has Got a Huge amount of Predefined Macros:-
 *    https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
 * 
 */

 /** pragma + include guard, cz its saferrrr, iguess.... & amVK_LOGGER is more like 'published' as separate gist too 😁 */
#pragma once
#ifndef REY_LOGGER_HH
#define REY_LOGGER_HH


#define amVK_LOG(x) amVK::cout << x << amVK::endl;
#define amVK_LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop) \
    amVK_LOG(""); \
    amVK_LOG(log_heading); \
    for (int iterator_var = 0, lim = static_cast<int>(loop_limit); iterator_var < lim; iterator_var++) { \
        amVK_LOG(log_inside_loop); \
    } \
    amVK_LOG("");

/**
   ╻ ╻   ╻  ┏━┓┏━╸   ┏━╸╻ ╻
   ╺╋╸   ┃  ┃ ┃┃╺┓   ┣╸ ┏╋┛
   ╹ ╹   ┗━╸┗━┛┗━┛╺━╸┗━╸╹ ╹
 */
#ifdef _WIN32
#define amVK_LOG_EX(x) amVK_LOG(x << "  [stackTrace below]: "); amVK_only_stacktrace(0); //Cuttoff from BLI_system_backtrace, only for windows....
#else
#define amVK_LOG_EX(x) amVK_LOG(x); BLI_system_backtrace(0); //linux does better job. and default BLI_system_backtrace is cool too!
#endif



 /** Made, so that we don't have to include <iostream> or <string> just cz we need to log */
class amVK_Logger {
  public:
    amVK_Logger() {}
    ~amVK_Logger() {}

    /** if it says 'more than one overload found': try this https://www.cplusplus.com/reference/ostream/ostream/operator<< */
    amVK_Logger& operator<<(const char c);
    amVK_Logger& operator<<(const char* txt);
    amVK_Logger& operator<<(const wchar_t* txt);
    amVK_Logger& operator<<(const int num);
    amVK_Logger& operator<<(const unsigned int num);
    amVK_Logger& operator<<(const unsigned long num); /** DWORD */
    amVK_Logger& operator<<(const unsigned long long num);
    amVK_Logger& operator<<(const double num);
    amVK_Logger& operator<<(const long long num);
    /** But we can't/don't wanna have support for stuffs like std::string */
};

class amVK_ConsoleInput {
  public:
    amVK_ConsoleInput() {}
   ~amVK_ConsoleInput() {}

    void get(void);
};

namespace amVK {
#ifdef REY_LOGGER_IMPLEMENTATION
    amVK_Logger cout = amVK_Logger();  /** 'console out' */
    char endl = '\n';
    amVK_ConsoleInput cin = amVK_ConsoleInput();  /** 'console in' */
#else
    extern amVK_Logger cout;
    extern char endl;
    extern amVK_ConsoleInput cin;
#endif
};




/**
 * for amVK Debug builds....
 *
 * the above ones [CORE] are the core ones
 *  - amVK_LOG
 *  - amVK_LOG_LOOP
 *  - amVK_LOG_EX
 *
 * the below ones [debug purposes]
 *  - _LOG   [debug for amVK devs]
 *  - _LOG0  [GENERAL Logging... e.g. vkCreateInsntace, vkCreateDevice etc....]
 */
#if defined(amVK_DEV_LOG)
#define _LOG(x) amVK_LOG(x)
#define _LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop) amVK_LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop)
#else
#define _LOG(x)
#define _LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop)
#endif

#if defined(amVK_ZEN_LOG)
#define _LOG0(x) amVK_LOG(x)
#define _LOG_LOOP0(log_heading, iterator_var, loop_limit, log_inside_loop) amVK_LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop)
#else
#define _LOG0(x)
#define _LOG_LOOP0(log_heading, iterator_var, loop_limit, log_inside_loop)
#endif





 /**
  * amVK_NoobTimer
  */
class _noob_timer;

/** Made, so that we don't have to include <iostream> or <string> or <chrono> in every other file.... */
class amVK_NoobTimer {
private:
    _noob_timer* m_NoobTimer = nullptr;
public:
    amVK_NoobTimer();
    ~amVK_NoobTimer();

    void init(void);
    void log(void);
    double get(void);
};

/** Make a array of this STRUCT (like below), then pass the  .time_spent to TIMER_STORE
 *   func_timer all[2] = {
 *     {"amVK_CreateDevice", 0.0},
 *     {"amVK_Pipeline", 0.0}
 *   };
 */
typedef struct noob_timer_store__ {
    char* func_name;
    double time_spent;
} noob_timer_store;

















/**
 *             ██╗███╗   ███╗██████╗ ██╗
 *   ▄ ██╗▄    ██║████╗ ████║██╔══██╗██║
 *    ████╗    ██║██╔████╔██║██████╔╝██║
 *   ▀╚██╔▀    ██║██║╚██╔╝██║██╔═══╝ ██║
 *     ╚═╝     ██║██║ ╚═╝ ██║██║     ███████╗
 *             ╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝
 */
#ifdef REY_LOGGER_IMPLEMENTATION
#include <iostream>
#include <fmt/core.h>
#include <fmt/xchar.h>
#define VK_CHECK(x)                                                     \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
             fmt::print("Detected Vulkan error: {}", string_VkResult(err)); \
            abort();                                                    \
        }                                                               \
    } while (0)
// THE NEXT VERSION WILL ME IMPLEMENTED BASED ON fmt
// https://github.com/fmtlib/fmt
// So i will be opening a SEMARATE REPO for this amVK_Logger
// This is the last update possibly for this GIST VERSION.

amVK_Logger& amVK_Logger::operator<<(const char c) {
    fmt::print("{}", c);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const char* txt) {
    fmt::print("{}", txt);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const wchar_t* txt) {
    fmt::print(L"{}", txt);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const int num) {
    fmt::print("{}", num);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const unsigned int num) {
    fmt::print("{}", num);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const unsigned long num) {
    fmt::print("{}", num);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const unsigned long long num) {
    fmt::print("{}", num);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const double num) {
    fmt::print("{}", num);
    return *this;
}
amVK_Logger& amVK_Logger::operator<<(const long long num) {
    fmt::print("{}", num);
    return *this;
}

void amVK_ConsoleInput::get(void) {
    std::cin.get();
}




#include <chrono>
class _noob_timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> time_start = {}, time_now = {};
} noob_timer;

amVK_NoobTimer::amVK_NoobTimer(void) {
    amVK_NoobTimer::init();
}

amVK_NoobTimer::~amVK_NoobTimer(void) {
    delete m_NoobTimer;
}

void amVK_NoobTimer::init(void) {
    if (m_NoobTimer == nullptr) {
        m_NoobTimer = new _noob_timer();
    }
    m_NoobTimer->time_start = std::chrono::high_resolution_clock::now();
}

void amVK_NoobTimer::log(void) {
    m_NoobTimer->time_now = std::chrono::high_resolution_clock::now();
    amVK_LOG(
        ((std::chrono::duration<double>)(m_NoobTimer->time_now - m_NoobTimer->time_start)).count()
    );
}

double amVK_NoobTimer::get(void) {
    m_NoobTimer->time_now = std::chrono::high_resolution_clock::now();
    return (double)((std::chrono::duration<double>)(m_NoobTimer->time_now - m_NoobTimer->time_start)).count();
}
#endif















/**
   ╻ ╻   ╻  ┏━┓┏━╸   ╺┳╸┏━┓   ┏━╸╻╻  ┏━╸
   ╺╋╸   ┃  ┃ ┃┃╺┓    ┃ ┃ ┃   ┣╸ ┃┃  ┣╸
   ╹ ╹   ┗━╸┗━┛┗━┛    ╹ ┗━┛   ╹  ╹┗━╸┗━╸

   USE:   blender.exe > debug_log.txt  2>&1 < %0 [blender_debug_log.cmd]
 */

 /**
  *             ██████╗ ██╗     ██╗           █████╗ ███████╗███████╗███████╗██████╗ ████████╗
  *   ▄ ██╗▄    ██╔══██╗██║     ██║          ██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗╚══██╔══╝
  *    ████╗    ██████╔╝██║     ██║          ███████║███████╗███████╗█████╗  ██████╔╝   ██║
  *   ▀╚██╔▀    ██╔══██╗██║     ██║          ██╔══██║╚════██║╚════██║██╔══╝  ██╔══██╗   ██║
  *     ╚═╝     ██████╔╝███████╗██║ ███████╗ ██║  ██║███████║███████║███████╗██║  ██║   ██║
  *             ╚═════╝ ╚══════╝╚═╝ ╚══════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝
  *
  * BLENDER: Modified version of https://github.com/blender/blender/blob/4b9ff3cd42be427e478743648e9951bf8c189a04/source/blender/blenlib/intern/system_win32.c
  *          \todo [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/creator/creator_signals.c#L206]
  *          \see downloads/blender-debug-log.txt
  *          \todo [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/blender/python/intern/bpy_interface.c#L475]
  *          \see  [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/creator/creator_signals.c#L183]
  *          \see [PYTHON BACKTRACE] (https://developer.blender.org/T91734)
  *          \todo [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/creator/creator_signals.c#L107]
  *
  *          \todo \see [https://developer.blender.org/T91767]    BLI_assert also produces     [blender.exe!] outputs....       when Richard runs into them....
  *                  Add this kinda Logging for WINDOWS.... [through mingW64?]    But this already is avail to WIN \see [https://developer.blender.org/T90620]
  *                but the File from here [https://developer.blender.org/T90999] seems more like what I get....
  *
  * ALT: [OBS] SetUnhandledExceptionFilter  [https://github.com/obsproject/obs-studio/blob/dde4d57d726ed6d9e244ffbac093d8ef54e29f44/libobs/obs-win-crash-handler.c]
  *            Blender also uses this [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/creator/creator_signals.c#L237]
  *       OBS does quite a Good Job....  see the online LOG Files: https://github.com/obsproject/obs-studio/issues/5324
  *       and for debug_log they use blog()   \see this linux error [Not Crash, Shutting DOWN] https://github.com/obsproject/obs-studio/issues/5189
  *                                           SEARCH: 'Failed to start screencast' in obs github code...   [one of the lines from the Issue Above]
  *      Couldn't find any CRASH LOG for linux  [https://github.com/obsproject/obs-studio/issues?q=+label%3ALinux++crash]
  *      BUT macOS SEGFAULT SystemTrace info is really COOL [https://github.com/obsproject/obs-studio/issues/4112]
  */

#if defined(_WIN32) || defined(__linux__) || defined(__APPLE__)
void BLI_system_backtrace(int output = 0);   //There are Other Cool usable BLI_*_* functions too inside #ifdef REY_LOGGER_IMPLEMENTATION
/** \todo impliment only stack trace till certain levels.... and not ABBORT.... */
#if defined(_WIN32)
void amVK_only_stacktrace(int output = 0);
#endif
#define amASSERT(x) if(x) BLI_system_backtrace(0)
#else
#error "amASSERT is only currently available for _WIN32 || __linux__ || __APPLE__"
#endif


  /** impl in amVK_Logger.cpp */
#ifdef REY_LOGGER_IMPLEMENTATION
#ifdef _WIN32
#include <windows.h>
#include <stdio.h>

#include <dbghelp.h>
#include <shlwapi.h>
#include <tlhelp32.h>

static EXCEPTION_POINTERS* current_exception = NULL;

static const char* bli_windows_get_exception_description(const DWORD exceptioncode)
{
    switch (exceptioncode) {
    case EXCEPTION_ACCESS_VIOLATION:
        return "EXCEPTION_ACCESS_VIOLATION";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
    case EXCEPTION_BREAKPOINT:
        return "EXCEPTION_BREAKPOINT";
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        return "EXCEPTION_DATATYPE_MISALIGNMENT";
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        return "EXCEPTION_FLT_DENORMAL_OPERAND";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
    case EXCEPTION_FLT_INEXACT_RESULT:
        return "EXCEPTION_FLT_INEXACT_RESULT";
    case EXCEPTION_FLT_INVALID_OPERATION:
        return "EXCEPTION_FLT_INVALID_OPERATION";
    case EXCEPTION_FLT_OVERFLOW:
        return "EXCEPTION_FLT_OVERFLOW";
    case EXCEPTION_FLT_STACK_CHECK:
        return "EXCEPTION_FLT_STACK_CHECK";
    case EXCEPTION_FLT_UNDERFLOW:
        return "EXCEPTION_FLT_UNDERFLOW";
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        return "EXCEPTION_ILLEGAL_INSTRUCTION";
    case EXCEPTION_IN_PAGE_ERROR:
        return "EXCEPTION_IN_PAGE_ERROR";
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        return "EXCEPTION_INT_DIVIDE_BY_ZERO";
    case EXCEPTION_INT_OVERFLOW:
        return "EXCEPTION_INT_OVERFLOW";
    case EXCEPTION_INVALID_DISPOSITION:
        return "EXCEPTION_INVALID_DISPOSITION";
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
    case EXCEPTION_PRIV_INSTRUCTION:
        return "EXCEPTION_PRIV_INSTRUCTION";
    case EXCEPTION_SINGLE_STEP:
        return "EXCEPTION_SINGLE_STEP";
    case EXCEPTION_STACK_OVERFLOW:
        return "EXCEPTION_STACK_OVERFLOW";
    default:
        return "UNKNOWN EXCEPTION";
    }
}

static void bli_windows_get_module_name(LPVOID address, PCHAR buffer, size_t size)
{
    HMODULE mod;
    buffer[0] = 0;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPSTR)address, &mod)) {
        if (GetModuleFileName(mod, buffer, size)) {
            PathStripPath(buffer);
        }
    }
}

static void bli_windows_get_module_version(const char* file, char* buffer, size_t buffersize)
{
    buffer[0] = 0;
    DWORD verHandle = 0;
    UINT size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD verSize = GetFileVersionInfoSize(file, &verHandle);
    if (verSize != 0) {
        LPSTR verData = (LPSTR)calloc(1, verSize);

        if (GetFileVersionInfo(file, verHandle, verSize, verData)) {
            if (VerQueryValue(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size)) {
                if (size) {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                    /* Magic value from
                    * https://docs.microsoft.com/en-us/windows/win32/api/verrsrc/ns-verrsrc-vs_fixedfileinfo
                    */
                    if (verInfo->dwSignature == 0xfeef04bd) {
                        printf(buffer,
                            buffersize,
                            "%d.%d.%d.%d",
                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
                            (verInfo->dwFileVersionMS >> 0) & 0xffff,
                            (verInfo->dwFileVersionLS >> 16) & 0xffff,
                            (verInfo->dwFileVersionLS >> 0) & 0xffff);
                    }
                }
            }
        }
        free(verData);
    }
}

static void bli_windows_system_backtrace_exception_record(FILE* fp, PEXCEPTION_RECORD record)
{
    char module[MAX_PATH];
    fprintf(fp, "Exception Record:\n\n");
    fprintf(fp,
        "ExceptionCode         : %s\n",
        bli_windows_get_exception_description(record->ExceptionCode));
    fprintf(fp, "Exception Address     : 0x%p\n", record->ExceptionAddress);
    bli_windows_get_module_name(record->ExceptionAddress, module, sizeof(module));
    fprintf(fp, "Exception Module      : %s\n", module);
    fprintf(fp, "Exception Flags       : 0x%.8x\n", record->ExceptionFlags);
    fprintf(fp, "Exception Parameters  : 0x%x\n", record->NumberParameters);
    for (DWORD idx = 0; idx < record->NumberParameters; idx++) {
        fprintf(fp, "\tParameters[%d] : 0x%p\n", idx, (LPVOID*)record->ExceptionInformation[idx]);
    }
    if (record->ExceptionRecord) {
        fprintf(fp, "Nested ");
        bli_windows_system_backtrace_exception_record(fp, record->ExceptionRecord);
    }
    fprintf(fp, "\n\n");
}



static bool BLI_windows_system_backtrace_run_trace(FILE* fp, HANDLE hThread, PCONTEXT context)
{
    const int max_symbol_length = 100;

    bool result = true;

    PSYMBOL_INFO symbolinfo = (PSYMBOL_INFO)calloc(1, sizeof(SYMBOL_INFO) + max_symbol_length * sizeof(char));
    symbolinfo->MaxNameLen = max_symbol_length - 1;
    symbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

    STACKFRAME frame = { 0 };
    frame.AddrPC.Offset = context->Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Rsp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrStack.Mode = AddrModeFlat;

    while (true) {
        if (StackWalk64(IMAGE_FILE_MACHINE_AMD64,
            GetCurrentProcess(),
            hThread,
            &frame,
            context,
            NULL,
            SymFunctionTableAccess64,
            SymGetModuleBase64,
            0)) {
            if (frame.AddrPC.Offset) {
                char module[MAX_PATH];

                bli_windows_get_module_name((LPVOID)frame.AddrPC.Offset, module, sizeof(module));

                if (SymFromAddr(GetCurrentProcess(), (DWORD64)(frame.AddrPC.Offset), 0, symbolinfo)) {
                    fprintf(fp, "%-20s:0x%p  %s", module, (LPVOID)symbolinfo->Address, symbolinfo->Name);
                    IMAGEHLP_LINE lineinfo;
                    lineinfo.SizeOfStruct = sizeof(lineinfo);
                    DWORD displacement = 0;
                    if (SymGetLineFromAddr(
                        GetCurrentProcess(), (DWORD64)(frame.AddrPC.Offset), &displacement, &lineinfo)) {
                        fprintf(fp, " %s:%d", lineinfo.FileName, lineinfo.LineNumber);
                    }
                    fprintf(fp, "\n");
                }
                else {
                    fprintf(fp,
                        "%-20s:0x%p  %s\n",
                        module,
                        (LPVOID)frame.AddrPC.Offset,
                        "Symbols not available");
                    result = false;
                    break;
                }
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    free(symbolinfo);
    fprintf(fp, "\n\n");
    return result;
}

static bool bli_windows_system_backtrace_stack_thread(FILE* fp, HANDLE hThread)
{
    CONTEXT context = { 0 };
    context.ContextFlags = CONTEXT_ALL;
    /* GetThreadContext requires the thread to be in a suspended state, which is problematic for the
    * currently running thread, RtlCaptureContext is used as an alternative to sidestep this */
    if (hThread != GetCurrentThread()) {
        SuspendThread(hThread);
        bool success = GetThreadContext(hThread, &context);
        ResumeThread(hThread);
        if (!success) {
            fprintf(fp, "Cannot get thread context : 0x0%.8x\n", GetLastError());
            return false;
        }
    }
    else {
        RtlCaptureContext(&context);
    }
    return BLI_windows_system_backtrace_run_trace(fp, hThread, &context);
}

static void bli_windows_system_backtrace_modules(FILE* fp)
{
    fprintf(fp, "Loaded Modules :\n");
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return;

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32)) {
        CloseHandle(hModuleSnap); /* Must clean up the snapshot object! */
        fprintf(fp, " Error getting module list.\n");
        return;
    }

    do {
        if (me32.th32ProcessID == GetCurrentProcessId()) {
            char version[MAX_PATH];
            bli_windows_get_module_version(me32.szExePath, version, sizeof(version));

            IMAGEHLP_MODULE64 m64;
            m64.SizeOfStruct = sizeof(m64);
            if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)me32.modBaseAddr, &m64)) {
                fprintf(fp,
                    "0x%p %-20s %s %s %s\n",
                    me32.modBaseAddr,
                    version,
                    me32.szModule,
                    m64.LoadedPdbName,
                    m64.PdbUnmatched ? "[unmatched]" : "");
            }
            else {
                fprintf(fp, "0x%p %-20s %s\n", me32.modBaseAddr, version, me32.szModule);
            }
        }
    } while (Module32Next(hModuleSnap, &me32));
}

static void bli_windows_system_backtrace_threads(FILE* fp)
{
    fprintf(fp, "Threads:\n");
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        fprintf(fp, "Unable to retrieve threads list.\n");
        return;
    }

    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32)) {
        CloseHandle(hThreadSnap);
        return;
    }
    do {
        if (te32.th32OwnerProcessID == GetCurrentProcessId()) {
            if (GetCurrentThreadId() != te32.th32ThreadID) {
                fprintf(fp, "Thread : %.8x\n", te32.th32ThreadID);
                HANDLE ht = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
                bli_windows_system_backtrace_stack_thread(fp, ht);
                CloseHandle(ht);
            }
        }
    } while (Thread32Next(hThreadSnap, &te32));
    CloseHandle(hThreadSnap);
}



static bool BLI_windows_system_backtrace_stack(FILE* fp)
{
    fprintf(fp, "Stack trace:\n");
    /* If we are handling an exception use the context record from that. */
    if (current_exception && current_exception->ExceptionRecord->ExceptionAddress) {
        /* The back trace code will write to the context record, to protect the original record from
        * modifications give the backtrace a copy to work on.  */
        CONTEXT TempContext = *current_exception->ContextRecord;
        return BLI_windows_system_backtrace_run_trace(fp, GetCurrentThread(), &TempContext);
    }
    else {
        /* If there is no current exception or the address is not set, walk the current stack. */
        return bli_windows_system_backtrace_stack_thread(fp, GetCurrentThread());
    }
}

static bool bli_private_symbols_loaded()
{
    IMAGEHLP_MODULE64 m64;
    m64.SizeOfStruct = sizeof(m64);
    if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)GetModuleHandle(NULL), &m64)) {
        return m64.GlobalSymbols;
    }
    return false;
}

static void bli_load_symbols()
{
    /* If this is a developer station and the private pdb is already loaded leave it be. */
    if (bli_private_symbols_loaded()) {
        return;
    }

    char pdb_file[MAX_PATH] = { 0 };

    /* get the currently executing image */
    if (GetModuleFileNameA(NULL, pdb_file, sizeof(pdb_file))) {
        /* remove the filename */
        PathRemoveFileSpecA(pdb_file);
        /* append blender.pdb */
        PathAppendA(pdb_file, "blender.pdb");
        if (PathFileExistsA(pdb_file)) {
            HMODULE mod = GetModuleHandle(NULL);
            if (mod) {
                WIN32_FILE_ATTRIBUTE_DATA file_data;
                if (GetFileAttributesExA(pdb_file, GetFileExInfoStandard, &file_data)) {
                    /* SymInitialize will try to load symbols on its own, so we first must unload whatever it
                    * did trying to help */
                    SymUnloadModule64(GetCurrentProcess(), (DWORD64)mod);

                    DWORD64 module_base = SymLoadModule(GetCurrentProcess(),
                        NULL,
                        pdb_file,
                        NULL,
                        (DWORD64)mod,
                        (DWORD)file_data.nFileSizeLow);
                    if (module_base == 0) {
                        fprintf(stderr,
                            "Error loading symbols %s\n\terror:0x%.8x\n\tsize = %d\n\tbase=0x%p\n",
                            pdb_file,
                            GetLastError(),
                            file_data.nFileSizeLow,
                            (LPVOID)mod);
                    }
                }
            }
        }
    }
}



void BLI_system_backtrace(int output)
{
    // amVK MOD
    FILE* fp = stdout;
    if (output == 1) {
        fp = stderr;
    }
    // amVK MOD
    SymInitialize(GetCurrentProcess(), NULL, TRUE);
    bli_load_symbols();
    if (current_exception) {
        bli_windows_system_backtrace_exception_record(fp, current_exception->ExceptionRecord);
    }
    if (BLI_windows_system_backtrace_stack(fp)) {
        /* When the blender symbols are missing the stack traces will be unreliable
        * so only run if the previous step completed successfully. */
        bli_windows_system_backtrace_threads(fp);
    }
    bli_windows_system_backtrace_modules(fp);
}

static void BLI_windows_handle_exception(EXCEPTION_POINTERS* exception)
{
    current_exception = exception;
    if (current_exception) {
        fprintf(stderr,
            "Error   : %s\n",
            bli_windows_get_exception_description(exception->ExceptionRecord->ExceptionCode));
        fflush(stderr);

        LPVOID address = exception->ExceptionRecord->ExceptionAddress;
        fprintf(stderr, "Address : 0x%p\n", address);

        CHAR modulename[MAX_PATH];
        bli_windows_get_module_name(address, modulename, sizeof(modulename));
        fprintf(stderr, "Module  : %s\n", modulename);
        fprintf(stderr, "Thread  : %.8x\n", GetCurrentThreadId());
    }
    fflush(stderr);
}

void amVK_only_stacktrace(int output)
{
    FILE* _fp = stdout;
    if (output == 1) {
        _fp = stderr;
    }

    SymInitialize(GetCurrentProcess(), NULL, TRUE);
    bli_load_symbols();
    BLI_windows_system_backtrace_stack(_fp);
}







#elif defined(__linux__) || defined(__APPLE__)
/**
 *            ██████╗ ██╗     ███████╗███╗   ██╗██╗     ██╗██████╗       ██╗  ██╗███╗   ██╗████████╗███████╗██████╗ ███╗   ██╗      ██╗  ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗    ██████╗
 *  ▄ ██╗▄    ██╔══██╗██║     ██╔════╝████╗  ██║██║     ██║██╔══██╗     ██╔╝  ██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗████╗  ██║     ██╔╝  ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║   ██╔════╝
 *   ████╗    ██████╔╝██║     █████╗  ██╔██╗ ██║██║     ██║██████╔╝    ██╔╝   ██║██╔██╗ ██║   ██║   █████╗  ██████╔╝██╔██╗ ██║    ██╔╝   ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║   ██║
 *  ▀╚██╔▀    ██╔══██╗██║     ██╔══╝  ██║╚██╗██║██║     ██║██╔══██╗   ██╔╝    ██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗██║╚██╗██║   ██╔╝    ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║   ██║
 *    ╚═╝     ██████╔╝███████╗███████╗██║ ╚████║███████╗██║██████╔╝  ██╔╝     ██║██║ ╚████║   ██║   ███████╗██║  ██║██║ ╚████║  ██╔╝     ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║██╗╚██████╗
 *            ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝╚═════╝   ╚═╝      ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══   ╚═╝      ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝ ╚═════╝
 *
 * copied from [https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/source/blender/blenlib/intern/system.c#L79]
 * Still BLI_ASSERT
 */

#include <execinfo.h>
 /**
  * Write a backtrace into a file for systems which support it.
  */
void BLI_system_backtrace(int output)
{
    // amVK MOD
    FILE* fp = stdout;
    if (output == 1) {
        fp = stderr;
    }
    // amVK MOD

    /* ------------- */
    /* Linux / Apple */
#  if defined(__linux__) || defined(__APPLE__)

#    define SIZE 100
    void* buffer[SIZE];
    int nptrs;
    char** strings;
    int i;

    /* include a backtrace for good measure */
    nptrs = backtrace(buffer, SIZE);
    strings = backtrace_symbols(buffer, nptrs);
    for (i = 0; i < nptrs; i++) {
        fputs(strings[i], fp);
        fputc('\n', fp);
    }
    fputc('\n', fp);

    free(strings);
#    undef SIZE

#  else
  /* ------------------ */
  /* non msvc/osx/linux */
    (void)fp;
#  endif
}
/* end BLI_system_backtrace */
#endif  //WIN32 || __linux__
#endif    // REY_LOGGER_IMPLEMENTATION



#endif    // REY_LOGGER_HH