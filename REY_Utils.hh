#pragma once

#ifndef REY_LOGGER_HH
  #include "REY_Logger.hh"
#endif
#include "REY_Types.hh"

/** 
 *  ╻ ╻   ┏━┓┏┳┓╻ ╻╻┏    ┏━┓┏━┓┏━┓┏━┓╻ ╻
 *  ╺╋╸   ┣━┫┃┃┃┃┏┛┣┻┓   ┣━┫┣┳┛┣┳┛┣━┫┗┳┛
 *  ╹ ╹   ╹ ╹╹ ╹┗┛ ╹ ╹╺━╸╹ ╹╹┗╸╹┗╸╹ ╹ ╹ 
 * 
 * \note if you use PUSH_BACK macro.... remember to set .data & .n first
 */
template<typename T>
struct REY_Array {
  T *data;            /** Pointer to the first element [But we dont do/keep_track_of MALLOC, cz.... DUH-Optimizations] */
  uint32_t n;
  uint32_t neXt = 0;  /** ahhh. neXt (2020) FX TV-series 😄 */

  /** CONSTRUCTOR - More like failsafes.... */
  REY_Array(T *D, uint32_t N) : data(D), n(N) {}
  REY_Array(T *D, uint32_t N, uint32_t NEXT) : data(D), n(N), neXt(NEXT) {}
  REY_Array(void) {data = nullptr; n = 0; neXt = 0;}
  ~REY_Array() {}

  /** 
   * inline hugely optimizes it, 
   * [the next inline copy-assignment func below too!] 
   */
  inline T& operator[](uint32_t index) {
    return data[index];
  }

  //filled
  inline size_t size(void) {return static_cast<size_t>(neXt);}
  inline size_t size_filled(void) {return static_cast<size_t>(neXt);}
  inline bool     is_filled(void) {return neXt >= n;}

  //size that can fit
  inline size_t size_alloced(void) {return static_cast<size_t>(n);}

  /** 
   * Default IMPLICIT copy-operator given by the compiler, TRY GodBolt 
   * \param otherArray: why const? https://www.cplusplus.com/articles/y8hv0pDG/  #Const correctness
   */
  inline REY_Array<T>& operator=(const REY_Array<T>& otherArray) {
    data = otherArray.data;
    n = otherArray.n;
    neXt = otherArray.neXt;
    return *this;
  }

  inline void reserve(uint32_t N) {
    data = new T[N];
    n = N;
  }
};

#define REY_Array_LOOP(_arr_, _iter_)for (uint32_t _iter_ = 0, lim = _arr_.n;                   _iter_ < lim; _iter_++)


#ifdef REY_UTILS_IMPLIMENTATION
  #include "string.h"
  #include "stdlib.h"
  void *REY_memcpy(void *to, void *from, size_t size) {
    return memcpy(to, from, size);
  }

  void *REY_malloc(size_t size) {
    return malloc(size);
  }

  void REY_ARRAY_PUSH_BACK_FILLED_LOG(uint32_t n, const char *var_name) { 
    if (n == 0) { 
      REY_LOG_EX("REY_Array<> " << var_name << ".n = 0;" << "Did you malloc? amASSERT here" << REY::endl); 
    }
    else {
      REY_LOG_EX("REY_Array FILLED!.... reUsing last SLOT"); 
    }
  }
#else
  void *REY_malloc(size_t size);
  void *REY_memcpy(void *to, void *from, size_t size);
  void REY_ARRAY_PUSH_BACK_FILLED_LOG(uint32_t n, const char *var_name);
#endif

/** reUse, cz we dont want it to Crash... and if doesn't have much effect */
#define REY_ARRAY_PUSH_BACK(var) \
  if (var.neXt >= var.n) { \
    REY_ARRAY_PUSH_BACK_FILLED_LOG(var.n, #var); \
    var.neXt--; \
  } \
  var.data[var.neXt++]

// Usage:- REY_ARRAY_PUSH_BACK(integer_array) = 10;
//         REY_ARRAY_PUSH_BACK(string_array) = "Hello World";

// use "SAFE" variants, when you "know" there is enough space
#define REY_ARRAY_PUSH_BACK_SAFE(var)    var.data[var.neXt++]
#define REY_ArrayDYN_PUSH_BACK_SAFE(var) var.data[var.neXt++]
#define REY_ArrayDYN_PUSH_BACK(var) \
    if (var.should_resize()) {var.resize();} \
        var.data[var.neXt++]


#define REY_ARRAY_IS_ELEMENT(array, bool_var, match_what) \
      for (uint32_t i = 0; i < array.n; i++) { \
        if (array.data[i] == match_what) { \
          bool_var = true; \
          break; \
        } \
      }




/** 
 * Dynamic Array.... a.k.a std::vector
 * .n doesn't mean size anymore.... use \fn size() 
 */
template<typename T> 
struct REY_ArrayDYN : public REY_Array<T> {
  REY_ArrayDYN(uint32_t N) : REY_Array<T>() {
    this->data = new T[N];
    this->n = N;
    this->neXt = 0;
  }
 ~REY_ArrayDYN() {}
  // Constructor that forwards parameters to the base class constructor
    REY_ArrayDYN(T* data, uint32_t n, uint32_t neXt) : REY_Array<T>(data, n, neXt) {}
    REY_ArrayDYN(T* data, uint32_t n) : REY_Array<T>(data, n) {}
    REY_ArrayDYN(void) : REY_Array<T>() {} 

  using REY_Array<T>::n;
  using REY_Array<T>::neXt;
  using REY_Array<T>::data;

  /** you can Delete this object instance after calling this function */
  inline void _delete(void) { delete[] this->data; }

  /** Only use this if `.data = nullptr` otherwise, memory-handle gone */
  void initialize(uint32_t N) {
    this->data = new T[N];
    this->n = N;
    this->neXt = 0;
  }

  /** Makes it 2X sized by default */
  void resize(double size_mul = 2);
  
  /**
   * neXt >= n
   * masterly advisory. unsteady content
   */
  inline bool should_resize(void) { return (bool)(this->neXt >= this->n); }

  /**
   * also see:- Preprocessor Macro:- `REY_ArrayDYN_PUSH_BACK()`
   */
  inline void push_back(T& element) {
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
      if (n != neXt-1) data[n] = data[neXt-1];
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

  if (this->n == 0) {
    this->data = new T[1];
    this->n = 1;
  }
  else {
    REY_ArrayDYN<T> _NewArray(this->n*size_mul);
    REY_memcpy(_NewArray.data, this->data, this->n * sizeof(T));
    delete[] this->data;

    this->data = _NewArray.data;
    this->n = _NewArray.n;
  }

  REY_LOG("Resizing Done");
}


/** GodBolt Test

      // [MemCpy based] Allows REY_Array<T> smth = {1, 2, 3, ...};     and    REY_Array<T> smth{1, 2, 3 };      why this [and not operator=] https://stackoverflow.com/q/16935295
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
*/





// VK_RESULT is int
#define REY_RESULT int32_t


/**
 *             ██████╗ ███████╗██╗   ██╗     ██╗   ██╗████████╗██╗██╗     ███████╗
 *   ▄ ██╗▄    ██╔══██╗██╔════╝╚██╗ ██╔╝     ██║   ██║╚══██╔══╝██║██║     ██╔════╝
 *    ████╗    ██████╔╝█████╗   ╚████╔╝      ██║   ██║   ██║   ██║██║     ███████╗
 *   ▀╚██╔▀    ██╔══██╗██╔══╝    ╚██╔╝       ██║   ██║   ██║   ██║██║     ╚════██║        ┏━  ┏┓╻┏━┓┏┳┓┏━╸┏━┓┏━┓┏━┓┏━╸┏━╸  ━┓
 *     ╚═╝     ██║  ██║███████╗   ██║███████╗╚██████╔╝   ██║   ██║███████╗███████║        ┃   ┃┗┫┣━┫┃┃┃┣╸ ┗━┓┣━┛┣━┫┃  ┣╸    ┃
 *             ╚═╝  ╚═╝╚══════╝   ╚═╝╚══════╝ ╚═════╝    ╚═╝   ╚═╝╚══════╝╚══════╝        ┗━  ╹ ╹╹ ╹╹ ╹┗━╸┗━┛╹  ╹ ╹┗━╸┗━╸  ━┛
 */
                                                                             
namespace REY_Utils {
/**
 * well.... 😉 see the implementation
 * \param how_far: How many bits [not BYTES] you wanna see
 * \param ptr: pointer to first bit   [a.k.a BYTE Technically]
 */
void memview2b(void *ptr, uint32_t how_far);

/**
 * BYTE    0: The Sign, NEGATIVE if '1', POSITIVE if '0'
 * BYTE  1-7: The Exponent, 1.0 = [0]01111111   [first zero is SIGN],    2.0 = [0]10000000, 4.0 = [0]10000001, 0.5 = [0]01111110
 * BYTE 8-31: The Mantisse....
 */
void view_fp32(float fp32);



/** 
 * TODO: Add support for ReverseSort
 * \param first_index: well the name says it
 * \param  last_index: as the name says. [index of \param unsorted]
 * \param    unsorted: the data that is used/compared to sort
 * \param   origIndex: should be as big as unsorted. Keeps track off OriginalIndexes of Elements from \param first_index to \param last_index
 */
template<typename T>  /** , typename uintXX_t   \todo change in the next commit */
bool mergeSort(uint32_t first_index, uint32_t last_index, T *unsorted, uint32_t *origIndex) {
  //First and 2nd Variable must be MALLOCED before. 2nd one should have filled numbers from zero to last index
    uint32_t n = last_index - first_index + 1;  //number of elements to sort
    if (n <= 1) {
        return true;
    } else if (n == 2) {
        if (unsorted[first_index] < unsorted[last_index]) {
            uint32_t tmp = unsorted[last_index];
            unsorted[last_index] = unsorted[first_index];
            unsorted[first_index] = tmp;

            uint32_t tmp2 = origIndex[last_index];
            origIndex[last_index] = origIndex[first_index];
            origIndex[first_index] = origIndex[tmp2];
            return true;
        }
    }

    uint32_t mid_index = first_index + (n / 2);
    mergeSort(first_index, mid_index, unsorted, origIndex);
    mergeSort(mid_index+1, last_index, unsorted, origIndex);

    //Finally Merge
    uint32_t p = first_index;               //First Half Start
    uint32_t p_lim = mid_index+1;           //First half End   +1 cz, we don't wanna do (p <= p_lim), we wanna do (p < p_lim)
    uint32_t q = p_lim;                     //Second Half Start
    uint32_t q_lim = last_index+1;          //Second Half End

    uint32_t *sorted_tmp = (uint32_t *) REY_malloc(n * sizeof(uint32_t));
    uint32_t *sorted_tmp2 = (uint32_t *) REY_malloc(n * sizeof(uint32_t));   //for origIndex
    uint32_t i = 0;
    while (true) {
        if (p == p_lim) {
            if (last_index-q != n-i-1) {REY_LOG("algorithm Failure code x010");}

            REY_memcpy(unsorted, sorted_tmp, i*sizeof(uint32_t));
            REY_memcpy(origIndex, sorted_tmp2, i*sizeof(uint32_t));
            //The Rest of unsorted is already SORTED
            return true;
        } 
        else if (q == q_lim) {
            if (mid_index-p != n-i-1) {REY_LOG("algorithm Failure code x010");}

            //Copy the rest of Unsorted-Left (a.k.a unsorted+p)
            REY_memcpy((unsorted+i), (unsorted+p), (p-first_index)*sizeof(uint32_t));
            REY_memcpy(unsorted, sorted_tmp, i*sizeof(uint32_t));

            REY_memcpy((origIndex+i), (origIndex+p), (p-first_index)*sizeof(uint32_t));
            REY_memcpy(origIndex, sorted_tmp2, i*sizeof(uint32_t));
            return true;
        }
        
        if (unsorted[p] < unsorted[q]) {
            sorted_tmp[i] = unsorted[q];
            sorted_tmp2[i] = origIndex[q];
            q++;
            i++;
        } else {
            sorted_tmp[i] = unsorted[p];
            sorted_tmp2[i] = origIndex[p];
            p++;
            i++;
        }
    }
    /** out of while(true) loop, code should never come this far */
}

} //namespace REY_Utils





#ifdef REY_UTILS_IMPLIMENTATION
#include <iostream>
#include <bitset>
#include <cmath>

void REY_Utils::memview2b(void *ptr, uint32_t how_far) {
    int n = ceil(how_far / 32);

    //we wanna show blocks of 32 bits
    uint32_t *xd = reinterpret_cast<uint32_t *> (ptr);
    REY_LOG("memview2b: ");
    for (int i = 0; i < n; i++) {
        std::bitset<32> y(*(xd + i));
        REY_LOG("  " << y.to_string().c_str() << "    - [" << (uint64_t)(xd + i) << "]");
    }
    REY_LOG("");
}

void REY_Utils::view_fp32(float fp32) {
    uint32_t the_input_int = *( reinterpret_cast<uint32_t *>(&fp32) );
    if (the_input_int & 0x80000000) {
        REY_LOG("-");
        the_input_int = (the_input_int << 1) >> 1;  //Wiki says right/left shift on unsigned int is gonna give '0' as new gen bits
    }
    REY_LOG("1.");
    REY_LOG(std::bitset<23>(the_input_int & 0x007FFFFF).to_string().c_str());   //0x007FFFF = Mantisse BIT-MASK
    REY_LOG(" * 2^" << (int)(the_input_int >> 23) - 127 << "\n\n");
}
#endif
