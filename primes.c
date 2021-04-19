// primes.c
// Řešení IJC-DU1, příklad a), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file primes.c
 *
 * @author Miroslav Šafář
 */

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "bitset.h"
#include "error.h"
#include "eratosthenes.h"

#ifdef USE_INLINE
extern inline void bitset_setbit(bitset_t bitset, bitset_index_t index, int value);
extern inline unsigned long bitset_getbit(bitset_t bitset, bitset_index_t index);
extern inline void bitset_free(bitset_t bitset);
extern inline unsigned long bitset_size(bitset_t bitset);
#endif

/**
 * Vypíše posledních 10 prvočísel do 200 000 000 na standartní výstup
 */
int main() {
    clock_t start = clock();
    bitset_create(bitset, 200000000UL);

    Eratosthenes(bitset);

    unsigned long N = bitset_size(bitset);

    //Vypíše posledních 10 prvočísel (Hodnota na jejich indexu je v bitovém poli po provedení Eratosthenova síta 0)
    unsigned long primes[10];
    int pi = 9;
    for (unsigned long i = N - 1; i > 1 && pi >= 0; i--) {
        if (bitset_getbit(bitset, i) == 0) {
            primes[pi] = i;
            pi--;
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%lu\n", primes[i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double) (clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
/*** Konec souboru primes.c ***/
