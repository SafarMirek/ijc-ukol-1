// error.c
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file error.c
 *
 * @author Miroslav Šafář
 */
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "error.h"

/**
 * Vypíše na stderr chybovou hlášku s podporou formátování
 *
 * @param fmt Chybová hláška
 */
void warning_msg(const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, arg_list);
}

/**
 * Vypíše na stderr chybovou hlášku s podporou formátování a ukončí program s chybovým kódem 1
 *
 * @param fmt Chybová hláška
 */
void error_exit(const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, arg_list);

    exit(1);
}
/*** Konec souboru error.c ***/
