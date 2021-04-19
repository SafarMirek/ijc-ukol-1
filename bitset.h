// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file bitset.h
 *
 * @author Miroslav Šafář
 */
#ifndef PROJEKT_1_BITSET_H
#define PROJEKT_1_BITSET_H

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "error.h"
#include <stdio.h>

#define UNSIGNED_LONG_BIT (sizeof(unsigned long) * CHAR_BIT)

typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_create(name, size) unsigned long name[(2UL + (size - 1UL) / UNSIGNED_LONG_BIT)] = {size, 0};static_assert(size > 0UL, "Velikost bitoveho pole musi byt kladna.")

#define bitset_alloc(name, size) \
assert(size > 0 && size <= ULONG_MAX);\
bitset_t name = calloc((2UL + (size - 1UL) / UNSIGNED_LONG_BIT), sizeof(unsigned long));\
if(name == NULL){\
error_exit("bitset_alloc: Chyba alokace paměti");\
}\
name[0] = (unsigned long) size

#ifndef USE_INLINE

#define bitset_free(name) (free(name))
#define bitset_size(name) (name[0])

#define bitset_setbit(name, index, expresion) \
do { \
if (index >= bitset[0] && index > 0) {\
error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) bitset[0]);\
}\
if (expresion) {\
bitset[1UL + index / UNSIGNED_LONG_BIT] |= (1UL << (index % UNSIGNED_LONG_BIT));\
} else {\
bitset[1UL + index / UNSIGNED_LONG_BIT] &= ~(1UL << (index % UNSIGNED_LONG_BIT));\
}\
}while(0)

#define bitset_getbit(name, index) ((index >= bitset[0] && index < 0) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) bitset[0]), 0) : ((bitset[1UL + (unsigned long) index / UNSIGNED_LONG_BIT] >> ((unsigned long) index % UNSIGNED_LONG_BIT)) & 1UL))

//#define bitset_setbit(name, index, expresion) if(index > name[0] || index < 0UL){/*TODO*/}if(expresion){;}else{;}

#else

inline void bitset_setbit(bitset_t bitset, bitset_index_t index, int value) {
    if (index >= bitset[0]) {
        error_exit("Error size");
    }

    if (value) {
        bitset[1UL + index / UNSIGNED_LONG_BIT] |= (1UL << (index % UNSIGNED_LONG_BIT));
    } else {
        bitset[1UL + index / UNSIGNED_LONG_BIT] &= ~(1UL << (index % UNSIGNED_LONG_BIT));
    }
}

inline unsigned long bitset_getbit(bitset_t bitset, bitset_index_t index) {
    return ((index >= bitset[0]) ? error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) bitset[0]), 0 : ((bitset[1UL + index / UNSIGNED_LONG_BIT] >> (index % UNSIGNED_LONG_BIT)) & 1UL));
}

inline void bitset_free(bitset_t bitset) {
    free(bitset);
}

inline unsigned long bitset_size(bitset_t bitset) {
    return bitset[0];
}

#endif // USE_INLINE

#endif //PROJEKT_1_BITSET_H

/*** Konec souboru bitset.h ***/
