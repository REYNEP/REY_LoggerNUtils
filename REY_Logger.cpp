#define REY_LOGGER_IMPLEMENTATION
#define REY_UTILS_IMPLIMENTATION
#define REY_STD_WRAP_IMPLIMENTATION
#include "REY_STDWrap.hh"
#include "REY_Logger.hh"
#include "REY_Utils.hh"



/**

  _____  ________     __       _____ _______ _______          __              
 |  __ \|  ____\ \   / /      / ____|__   __|  __ \ \        / /              
 | |__) | |__   \ \_/ /      | (___    | |  | |  | \ \  /\  / / __ __ _ _ __  
 |  _  /|  __|   \   /        \___ \   | |  | |  | |\ \/  \/ / '__/ _` | '_ \ 
 | | \ \| |____   | |         ____) |  | |  | |__| | \  /\  /| | | (_| | |_) |
 |_|  \_\______|  |_|        |_____/   |_|  |_____/   \/  \/ |_|  \__,_| .__/ 
                  ______ ______                                        | |    
                 |______|______|                                       |_|    
 
 */
void REY_strcpy_s(char *to, rsize_t to_bytes_max, const char *from) {
    rsize_t from_bytes = strlen(from) + 1;

    if (from_bytes > to_bytes_max) {
        REY_LOG_EX("[REY_STDWrap.h :: REY_strcpy_safe()]:- \n"
                << "    from_bytes [strlen(from) + 1] > to_bytes_max \n" 
                << "    -----> See function docs \n");

        return;
    }

    #ifdef _MSC_VER
        errno_t err = strcpy_s(to, to_bytes_max, from);
        if (err != 0) {
            char errorMessage[256]; // Buffer to store the error message
            strerror_s(errorMessage, sizeof(errorMessage), err); // Retrieve the error message

            REY_LOG_EX("[REY_STDWrap.h :: REY_strcpy_safe()]:- \n"
                    << "    strcpy_s failed with error code: " << err << "\n"
                    << "    Error message[256bytes]: " << errorMessage << "\n"
                    << "    Possible reasons: \n"
                    << "        - Destination buffer is too small.\n"
                    << "        - Invalid pointers passed to the function.");
        }
    #else
        strcpy(to, from);
    #endif
}