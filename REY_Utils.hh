#pragma once

#ifndef REY_LOGGER_HH
  #include "REY_Logger.hh"
#endif
#include "REY_STDWrap.hh"

    //  VK_RESULT is int
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
