// eratosthenes.c
// Řešení IJC-DU1, příklad a), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file eratosthenes.c
 *
 * @author Miroslav Šafář
 */

#include "eratosthenes.h"
#include "bitset.h"
#include "error.h"

#include <math.h>

/**
 * Funkce vykoná eratostenovo síto nad bitovým polem. Na prvočíselných indexech zůstane 0, jinak 1.
 *
 * @param bitset Bitset, nad kterým se vykoná eratosthenovo síto
 */
void Eratosthenes(bitset_t bitset) {
    unsigned long N = bitset_size(bitset);
    if (N == 0) return;
    bitset_setbit(bitset, 0, 1);
    if (N == 1) return;
    bitset_setbit(bitset, 1, 1);

    unsigned long sq = (unsigned long) sqrt(bitset_size(bitset));
    for (unsigned long i = 2; i <= sq; ++i) {
        if (bitset_getbit(bitset, i) == 0) {
            for (unsigned long n = 2 * i; n < N; n += i) {
                bitset_setbit(bitset, n, 1);
            }
        }
    }
}
/*** Konec souboru eratosthenes.c ***/
