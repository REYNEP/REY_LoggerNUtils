#pragma once
#include "REY_Types.hh"
#include "REY_Logger.hh"
#include "REY_STDWrap.hh"

/** 
 *  ╻ ╻   ┏━┓┏┳┓╻ ╻╻┏    ┏━┓┏━┓┏━┓┏━┓╻ ╻
 *  ╺╋╸   ┣━┫┃┃┃┃┏┛┣┻┓   ┣━┫┣┳┛┣┳┛┣━┫┗┳┛
 *  ╹ ╹   ╹ ╹╹ ╹┗┛ ╹ ╹╺━╸╹ ╹╹┗╸╹┗╸╹ ╹ ╹ 
 */
#pragma region REY_Array

template<typename T>
struct REY_Array {
    T *data;            /** Pointer to the first element [But we dont do/keep_track_of MALLOC, cz.... DUH-Optimizations] */
    uint32_t MAL;       /** malloced (memory allocated) Elements Count 💁‍♀️ [MAL from Shadow & Bones (2021)] */
    uint32_t neXt;      /** ahhh. neXt (2020) FX TV-series 😄 */

    /** ====================== CONSTRUCTOR - More like failsafes....  ====================== */
     REY_Array(T *D, uint32_t MAL)                : data(D),          MAL(MAL),   neXt(MAL)   {}
     REY_Array(T *D, uint32_t MAL, uint32_t NEXT) : data(D),          MAL(MAL),   neXt(NEXT)  {}
     REY_Array(void)                         {this->data = nullptr; this->MAL = 0; this->neXt = 0;}
    ~REY_Array() {}


    /** ====================== size that can fit  ====================== */
    inline size_t size_alloced(void){return static_cast<size_t>(MAL);}
    inline size_t size(void)        {return static_cast<size_t>(neXt);}
    inline size_t size_filled(void) {return static_cast<size_t>(neXt);}
    inline bool     is_filled(void) {return neXt >= MAL;}

    /** @param MAL: `this->MAL = MAL;` `this->neXt = MAL` */
    inline void reserve(uint32_t MAL, bool set_neXt_zero = false) {  // SET: neXt = 0 ---> if you wanna push_back
        if (MAL == 0) {return;}
        this->data = new T[MAL];
        this->MAL  = MAL;
        if (set_neXt_zero) {this->neXt = 0;}
        else               {this->neXt = MAL;}
    }
    inline void malloc(uint32_t MAL, bool set_neXt_zero = false) {   // Doesn't use the "NEW" operator
        if (MAL == 0) {return;}
        this->data = static_cast<T*>(REY_malloc(sizeof(T) * MAL));
        this->MAL  = MAL;
        if (set_neXt_zero) {this->neXt = 0;}
        else               {this->neXt = MAL;}
    }
    inline void free(void) {
        delete this->data;
        this->MAL  = 0;
        this->neXt = 0;
    }

    void non_dynamic_push_back_safety(const char *var_name) { 
        if (MAL == 0)         { REY_LOG_EX("REY_Array<> " << var_name << ".MAL = 0;       [            Did you malloc?          ] "); reserve(1, 0);  }
        else if (neXt == MAL) { REY_LOG_EX("REY_Array<> " << var_name << ".MAL == .next   [          a.k.a. it's FILLED!        ] "); neXt = MAL - 1; }
        else if (neXt >= MAL) { REY_LOG_EX("REY_Array<> " << var_name << ".MAL >= .next   [THIS SHOULD NEVER HAPPEN aaaaaaa! 😭] "); neXt = MAL - 1; }
    }

    /** ====================== operator[] =========================
     * inline hugely optimizes it, 
     * [the next inline copy-assignment func below too!]         */
    inline T& operator[](uint32_t index) {
        return data[index];
    }
    /** ======================            ====================== */
    
    /** 
     * Default IMPLICIT copy-operator given by the compiler, TRY GodBolt 
     * \param otherArray: why const? https://www.cplusplus.com/articles/y8hv0pDG/  #Const correctness
     */
    inline REY_Array<T>& operator=(const REY_Array<T>& otherArray) {
        this->data = otherArray.data;
        this->MAL  = otherArray.MAL;
        this->neXt = otherArray.neXt;
        return *this;
    }

    /** ====================== WIP ---> New constructor for initializer lists ======================
    REY_Array(std::initializer_list<T> list) {
        this->data = new T[MAL];
        this->MAL    = list.size();
            memcpy(data, list.begin(), MAL * sizeof(T));
        this->neXt = MAL;
    }
    ================================================================================================ */
};
#pragma endregion








#pragma region MACROS

// Prefix:- _x_ [underscored suffix + prefix] --> specify a variable name. You can use this variable 

#define REY_Array_LOOP(ARRAY,               _k_)      for (uint32_t _k_ = 0, lim = ARRAY.neXt; _k_ < lim; _k_++)
#define REY_Array_INIT(ARRAY,        MAL, VALUE)   \
                       ARRAY.reserve(MAL, 0);      \
                       ARRAY.neXt =  MAL;          \
        REY_Array_LOOP(ARRAY, rey_k) { ARRAY[rey_k] = VALUE; }

#define REY_Array_INITIALIZE(a, b, c) \
        REY_Array_INIT      (a, b, c)

#define REY_Array_RESERVE(ARRAY, MAL) ARRAY.reserve(MAL, set_neXt_zero = false)
#define REY_Array_MALLOC( ARRAY, MAL) ARRAY.malloc (MAL, set_neXt_zero = false)

#define REY_Array_IS_ELEMENT(ARRAY,     _k_,    match_what, out_boolean)    \
              REY_Array_LOOP(ARRAY,     _k_) {                              \
                        if  (ARRAY.data[_k_] == match_what) {               \
                            out_boolean = true; \
                            break; \
                        } \
              }

#define REY_ArrayDYN_LOOP(ARRAY, _k_) REY_Array_LOOP(ARRAY, _k_)

/** ========================= ikSAFE = I Know SAFE ========================= */
    #define    REY_ARRAY_PUSH_BACK_ikSAFE(A) A.data[A.neXt++]
    #define REY_ArrayDYN_PUSH_BACK_ikSAFE(A) A.data[A.neXt++]
/** ======= use these variants, when you "know" there is enough space ====== */

/** =========================       PUSH BACK      ========================= */
    #define REY_ArrayDYN_PUSH_BACK(A)           \
        if (A.neXt >= A.MAL)      {A.resize();} \
        A.data[A.neXt++]

    #define         REY_ARRAY_PUSH_BACK(A) \
        A.non_dynamic_push_back_safety(#A) \
        A.data[A.neXt++]

    // Usage:- REY_ARRAY_PUSH_BACK(integer_array) = 10;
    //         REY_ARRAY_PUSH_BACK(string_array)  = "Hello World";
/** =========================       PUSH BACK      ========================= */

#pragma endregion






/** 
  ╻ ╻   ┏━┓┏━╸╻ ╻   ┏━┓┏━┓┏━┓┏━┓╻ ╻╺┳┓╻ ╻┏┓╻
  ╺╋╸   ┣┳┛┣╸ ┗┳┛   ┣━┫┣┳┛┣┳┛┣━┫┗┳┛ ┃┃┗┳┛┃┗┫
  ╹ ╹   ╹┗╸┗━╸ ╹ ╺━╸╹ ╹╹┗╸╹┗╸╹ ╹ ╹ ╺┻┛ ╹ ╹ ╹
 */
#pragma region REY_ArrayDYN

/** 
 * Dynamic Array.... a.k.a std::vector
 * .n doesn't mean size anymore.... use \fn size() 
 */
template<typename T> 
struct REY_ArrayDYN      : public REY_Array<T> {
    REY_ArrayDYN(uint32_t  MAL) : REY_Array<T>() {
        this->data = new T[MAL];
        this->MAL = MAL;
        this->neXt = 0;
    }
    ~REY_ArrayDYN() {}

    // Constructor that forwards parameters to the base class constructor
        REY_ArrayDYN(T* data, uint32_t MAL, uint32_t neXt)    : REY_Array<T>(data, MAL, neXt) {}
        REY_ArrayDYN(T* data, uint32_t MAL)                   : REY_Array<T>(data, MAL) {}
        REY_ArrayDYN(void)                                    : REY_Array<T>() {
            this->data = nullptr;
            this->MAL  = 0;
            this->neXt = 0;
        } 

    using REY_Array<T>::MAL;
    using REY_Array<T>::neXt;
    using REY_Array<T>::data;

    /** you can Delete this object instance after calling this function */
    inline void _delete(void) { delete[] this->data; }

    /** Only use this if `.data = nullptr` otherwise, memory-handle gone */
    void initialize(uint32_t MAL) {
        this->data = new T[MAL];
        this->MAL  = MAL;
        this->neXt = 0;
    }

    /** Makes it 2X sized by default */
    void resize(double size_mul = 2);
    
    /**
     * neXt >= n
     * masterly advisory. unsteady content
     */
    inline bool should_resize(void) { return (bool)(this->neXt >= this->MAL); }

    /** TRY:- `REY_ArrayDYN_PUSH_BACK()` if you need 1000s of push_backs */
    inline void push_back(const T& element) {
        if (should_resize()) {resize();}
        this->data[neXt++] = element;
    }

    /**
     * data[n] = data[neXt-1]
     * masterly advisory. unsteady content
     */
    inline void lazy_erase(uint32_t n) {
        if (neXt <= 1) neXt = 0;
        else {
            if (n != neXt-1) { data[n] = data[neXt-1]; }
            neXt--;
        }
    }

    /**
     * neXt--;
     * masterly advisory. unsteady content
     */
    inline void lazy_erase_last_elem(void) { neXt--; }
};

template<typename T>
void REY_ArrayDYN<T>::resize(double size_mul) {
    REY_LOG("Resizing array");

    if (this->MAL == 0) {
        this->data = new T[1];
        this->MAL  = 1;
    }
    else {
        REY_ArrayDYN<T> _NewArray(this->MAL*size_mul);
        REY_memcpy(_NewArray.data, this->data, this->MAL * sizeof(T));
        delete[] this->data;

        this->data = _NewArray.data;
        this->MAL  = _NewArray.MAL;
    }

    REY_LOG("Resizing Done");
}

#pragma endregion

/**  ============================================== GodBolt Test ==============================================

      // [MemCpy based] Allows REY_Array<T> smth = {1, 2, 3, ...};     and    REY_Array<T> smth{1, 2, 3 };      
      // why this [and not operator=] https://stackoverflow.com/q/16935295

      REY_Array(std::initializer_list<T> ilist) {
        n = ilist.size();
        // if (n > 0) {  Not really needed: [https://stackoverflow.com/q/1087042], tho we must delete...
        data = new T[n];                            //do remember to delete[] yourself
        memcpy(data, ilist.begin(), n * sizeof(T));
        neXt = n;
      }
      // For Optimization Purposes....  when called in 2 lines REY_Array<T> smth; smth = {1, 2, 3};
      REY_Array<T>& operator=(std::initializer_list<T> ilist) {
        n = ilist.size();
        data = new T[n];
        memcpy(data, ilist.begin(), n * sizeof(T));
        neXt = n;

        return *this;
        // \todo maybe impl. a safe DEBUG impl. like in https://www.cplusplus.com/articles/y8hv0pDG/
      }

      int main(void) {
        // Calls CONSTRUCTOR with initializer list
        REY_Array<double> bunch_of_doubles2 = {100.0, 200.0};

        // Calls default constructor
        REY_Array<double> bunch_of_doubles;
        // Calls operator=
        bunch_of_doubles = {0.0, 1.0, 2.0, 3.0};
        // So combining both of these actually saves CPU time

        REY_Array<double> another_bunch_of_doubles = bunch_of_doubles;
        return 0;
      }
     ============================================== GodBolt Test ============================================== */