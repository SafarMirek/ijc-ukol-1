// steg-decode.c
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file steg-decode.c
 *
 * @author Miroslav Šafář
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"

/**
 * Vypíše zprávu zašifrovanout do obrázku formátu ppm na standartní výstup
 * Bity zprávy se nachází na LSB u bytů na prvočíselném indexu >= 23
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        error_exit("Invalid arguments...\n");
    }
    struct ppm *result = ppm_read(argv[1]);
    if (result == NULL) {
        error_exit("Chybný formát souboru");
    }

    bitset_alloc(bitset, 3L * result->xsize * result->ysize);

    Eratosthenes(bitset);

    unsigned char c = 0;
    unsigned msg_i = 0;

    for (unsigned i = 23; i < bitset_size(bitset); i++) {
        if (bitset_getbit(bitset, i) == 0) {
            c |= ((result->data[i] & 1UL) << msg_i++);
        }
        if (msg_i == 8) {
            if (c == '\0') {
                break;
            }
            putchar(c);
            msg_i = 0;
            c = 0;
        }
    }

    ppm_free(result);
    bitset_free(bitset);

    if (c != '\0') {
        error_exit("Chybný formát souboru");
    }

    putchar('\n');
    return 0;
}

/*** Konec souboru steg-decode.c ***/
