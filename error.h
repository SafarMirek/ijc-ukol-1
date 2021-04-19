// error.h
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Miroslav Šafář (xsafar23), FIT
// Přeloženo: gcc 7.5
/**
 * @file error.h
 *
 * @author Miroslav Šafář
 */

#ifndef PROJEKT_1_ERROR_H
#define PROJEKT_1_ERROR_H

/**
 * Vypíše na stderr chybovou hlášku s podporou formátování
 *
 * @param fmt Chybová hláška
 */
void warning_msg(const char *fmt, ...);

/**
 * Vypíše na stderr chybovou hlášku s podporou formátování a ukončí program s chybovým kódem 1
 *
 * @param fmt Chybová hláška
 */
void error_exit(const char *fmt, ...);

#endif //PROJEKT_1_ERROR_H
/*** Konec souboru error.h ***/
