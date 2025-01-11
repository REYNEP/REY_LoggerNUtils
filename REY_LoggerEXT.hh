/** 
 * std libraries like iostream or string actually is like 50K lines long 
 * 
 * so you can use alternative amVK::cout ['console out']
 * if you define this, won't include <iostream>
 */

  #include <iostream>
  #define LOG(x) std::cout << x << std::endl

  #define LOG_INDENTATION "  "
  #define LOG_0() ""
  #define LOG_1() LOG_0() << LOG_INDENTATION
  #define LOG_2() LOG_1() << LOG_INDENTATION
  #define LOG_3() LOG_2() << LOG_INDENTATION
  #define LOG_4() LOG_3() << LOG_INDENTATION
  #define LOG_5() LOG_4() << LOG_INDENTATION
  #define LOG_6() LOG_5() << LOG_INDENTATION
  #define LOG_LVL(LVL, x) LOG(LOG_##LVL << x)

  #define LOG_LOOP_TYPE_CAST(x) static_cast<int>(x)
  #define LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop) \
      LOG(""); \
      LOG(log_heading); \
      for (int iterator_var = 0, lim = LOG_LOOP_TYPE_CAST(loop_limit); iterator_var < lim; iterator_var++) { \
          LOG(log_inside_loop); \
      } \
      LOG("");


  /**
   * LOGGER MK2
   * __FUNCTION__, __func__ are not Macros, rather they are Variables that the compiler defines....
   * But the reason why LOG_DBG Works is because LOG_DBG uses another function LOG which doesn't let __LINE__ to be converted directly on this files line 55
   * \todo cehck gcc Part: https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html
   */
  #include <typeinfo>
  #if defined(__GNUC__)
    #define __FUNCINFO__ __FUNCTION__
    #define __FUNC_MANGLED__ typeid(__FUNCINFO__).name()
  #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define __FUNCINFO__ __func__
    #define __FUNC_MANGLED__ typeid(__FUNCINFO__).name()
  #elif defined(_MSC_VER)
    #define __FUNCINFO__ __func__
    #define __FUNC_MANGLED__ __FUNCDNAME__
  #else
    #define __FUNCINFO__ "[__FUNCTION__ or __func__ not supported by current compiler]"
    #define __FUNC_MANGLED__ typeid(__FUNCINFO__).name()
  #endif


  #define LOG_DBG(x) LOG("MANGLED NAME:- " << __FUNC_MANGLED__ << std::endl \
                      << __FILE__ << " || Function: " << __FUNCINFO__ << "() - Line" << __LINE__ << std::endl \
                      << " Log-Message:- " << x << std::endl)

  /**
    ╻ ╻   ╻  ┏━┓┏━╸   ┏━╸╻ ╻
    ╺╋╸   ┃  ┃ ┃┃╺┓   ┣╸ ┏╋┛
    ╹ ╹   ┗━╸┗━┛┗━┛╺━╸┗━╸╹ ╹
  */
  #ifdef _WIN32
    #define LOG_EX(x) LOG(x << "  [stackTrace below]: "); amVK_only_stacktrace(stderr); //Cuttoff from BLI_system_backtrace, only for windows....
  #else
    #define LOG_EX(x) LOG(x); BLI_system_backtrace(stderr); //linux does better job. and default BLI_system_backtrace is cool too!
  #endif





  /** 
   * Options to turn off parts of LOGGER, support....
   * Options that should be turned on/off from Makefiles
   * 
   * MK1: [old stuffs made during MK1.... amVK_CX]
   * MK2: everything that is in MK2....
   */
  #if defined(amVK_MK1_NOOB_LOG)
    #define LOG_MK1(x) LOG(x)
    #define LOG_LOOP_MK1(log_heading, iterator_var, loop_limit, log_inside_loop) LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop)
  #else
    #define LOG_MK1(x)
    #define LOG_LOOP_MK1(log_heading, iterator_var, loop_limit, log_inside_loop)
  #endif

  #if defined(amVK_MK2_NOOB_LOG)
    #define LOG_MK2(x) LOG(x)
    #define LOG_LOOP_MK2(log_heading, iterator_var, loop_limit, log_inside_loop) LOG_LOOP(log_heading, iterator_var, loop_limit, log_inside_loop)
  #else
    #define LOG_MK2(x)
    #define LOG_LOOP_MK2(log_heading, iterator_var, loop_limit, log_inside_loop)
  #endif

  #if defined(amVK_HISTORY)
    #define amFUNC_HISTORY() LOG(__FUNC_MANGLED__)
  #else
    #define amFUNC_HISTORY()
  #endif
  #if defined(amVK_HISTORY_INTERNAL)
    #define amFUNC_HISTORY_INTERNAL() LOG(__FUNC_MANGLED__)
  #else
    #define amFUNC_HISTORY_INTERNAL()
  #endif