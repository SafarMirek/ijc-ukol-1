// eratosthenes.h
// Řešení IJC-DU1, příklad a), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file eratosthenes.h
 *
 * @author Miroslav Šafář
 */
#ifndef PROJEKT_1_ERATOSTHENES_H
#define PROJEKT_1_ERATOSTHENES_H

#include "bitset.h"

/**
 * Funkce vykoná eratostenovo síto nad bitovým polem. Na prvočíselných indexech zůstane 0, jinak 1.
 *
 * @param bitset Bitset, nad kterým se vykoná eratosthenovo síto
 */
void Eratosthenes(bitset_t pole);

#endif //PROJEKT_1_ERATOSTHENES_H
/*** Konec souboru eratosthenes.h ***/
