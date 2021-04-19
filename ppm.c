// ppm.c
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file ppm.c
 *
 * @author Miroslav Šafář
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ppm.h"
#include "error.h"

#define NUMBER_LENGHT 10 //Maximální podporovaná délka čísla

/**
 * Zjistí, zda je charakter bílý znak
 *
 * @param c Charakter
 * @return Vrátí True pokud je charakter bílý znak, jinak False
 */
bool isWhiteSpace(unsigned char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

/**
 * Zjistí, zda je charakter číslice
 *
 * @param c Charakter
 * @return Vrátí True pokud je charakter číslice, jinak False
 */
bool isNumeralZero(unsigned char c) {
    return (c >= '0' && c <= '9');
}

/**
 * Zjistí, zda je charakter číslice 1-9
 *
 * @param c Charakter
 * @return Vrátí True pokud je charakter číslice 1-9, jinak False
 */
bool isNumeral(unsigned char c) {
    return (c >= '1' && c <= '9');
}

/**
 * Dekóduje soubor formátu ppm do struktury ppm a vrátí na ni ukazatel
 *
 * @param filename Název souboru formátu ppm
 * @return Vrátí ukazatel na strukturu ppm
 */
struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        warning_msg("Permissions denied %s", filename);
        return NULL;
    }

    struct ppm *result = NULL;

    char a_number[NUMBER_LENGHT]; // Aktuálně zpracovávané číselného parametru
    int number_index = 0; // Index číslice aktuálně zpracovávaného čísla

    unsigned params[3]; // Číselné parametry formátů : Width | Height | Maximul value for each color
    int param_i = 0; // Index aktuálně zpracovávaného parametr

    unsigned long data_i = 0; //Index zpracovávaného bytu

    bool invalid_format = false;
    int state = 0; // Aktuální stav stavového automatu
    int c;
    while ((c = fgetc(file)) != EOF && !invalid_format) {
        switch (state) {
            case 0:
                if (c == 'P') { state = 1; }
                else { invalid_format = true; }
                break;
            case 1:
                if (c == '6') {
                    state = 2;
                } else {
                    invalid_format = true;
                }
                break;
            case 2:
                if (isWhiteSpace(c)) {
                    state = 3;
                } else {
                    invalid_format = true;
                }
                break;
            case 3:
                if (isWhiteSpace(c)) {
                    break;
                } else if (isNumeral(c)) { // počáteční číslice musí být 1-9
                    state = 4;
                    a_number[number_index++] = c;
                } else {
                    invalid_format = true;
                }
                break;
            case 4:
                if (isNumeralZero(c)) {
                    if (number_index >= NUMBER_LENGHT) {
                        invalid_format = true;
                        break;
                    }
                    a_number[number_index++] = c;
                } else if (isWhiteSpace(c)) {
                    a_number[number_index] = '\0';
                    char *ptr;
                    unsigned long param = strtoul(a_number, &ptr, 10);
                    if (!ptr) {
                        invalid_format = true;
                        break;
                    }
                    params[param_i++] = param;
                    if (param_i <= 2) {
                        state = 3;
                        number_index = 0;
                        break;
                    }
                    state = 5;

                    if (params[2] != 255) {
                        invalid_format = true;
                        break;
                    }

                    result = malloc(sizeof(struct ppm) + (3 * params[0] * params[1]));
                    if (result == NULL) {
                        warning_msg("NO FREE MEMORY");
                        invalid_format = true;
                    }
                    result->xsize = params[0];
                    result->ysize = params[1];
                } else {
                    invalid_format = true;
                }
                break;
            case 5:
                if (data_i >= 3 * result->xsize * result->ysize) {
                    invalid_format = true;
                    break;
                }
                result->data[data_i++] = c;
                break;
        } // switch(case)
    }
    if (invalid_format) {
        warning_msg("Neplatný formát souboru %s\n", filename);
        if (result != NULL) {
            ppm_free(result);
            result = NULL;
        }
    }
    fclose(file);
    return result;
}

/**
 * Uvolní strukturu ppm z paměti
 *
 * @param ppm Ukazatel na strukturu ppm do paměti
 */
void ppm_free(struct ppm *p) {
    free(p);
}

/*** Konec souboru ppm.c ***/
