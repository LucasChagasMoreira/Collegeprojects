#include <stdbool.h>

#define WORDS_SIZE 4
#define INVALID_ADD -1
#define COST_ACCESS_L1 1
#define COST_ACCESS_L2 10
#define COST_ACCESS_L3 100
#define COST_ACCESS_RAM 1000
// #define PRINT_INTERMEDIATE_RAM
// #define PRINT_LOG

//#define DIRECT_MAPPING

#define ASSOCIATIVE_MAPPING

#ifdef ASSOCIATIVE_MAPPING
    #define LFU
    //#define LRU
    //#define FIFO
    //#define RANDOM
#endif
