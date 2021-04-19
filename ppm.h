// ppm.h
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file ppm.h
 *
 * @author Miroslav Šafář
 */

#ifndef PROJEKT_1_PPM_H
#define PROJEKT_1_PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

/**
 * Dekóduje soubor formátu ppm do struktury ppm a vrátí na ni ukazatel
 *
 * @param filename Název souboru formátu ppm
 * @return Vrátí ukazatel na strukturu ppm
 */
struct ppm *ppm_read(const char *filename);

/**
 * Uvolní strukturu ppm z paměti
 *
 * @param ppm Ukazatel na strukturu ppm do paměti
 */
void ppm_free(struct ppm *p);

#endif //PROJEKT_1_PPM_H
/*** Konec souboru ppm.h ***/
