#ifndef FORMATTER_H
#define FORMATTER_H

#include "image.h"

/**
 * @brief Zmeni format libovolneho obrazku na BMP 1b
 * @param src - Zdrojovy obrazek
 * @param dst - Cilovy obrazek (vstupuje do funkce jako nealokovany)
 * @return Error code
 */
extern int FORMATTER_formatToBMP1(Image *src, Image **dst);

/**
 * @brief Zmeni format libovolneho obrazku na BMP 4b
 * @param src - Zdrojovy obrazek
 * @param dst - Cilovy obrazek (vstupuje do funkce jako nealokovany)
 * @return Error code
 */
extern int FORMATTER_formatToBMP4(Image *src, Image **dst);

/**
 * @brief Zmeni format libovolneho obrazku na BMP 8b
 * @param src - Zdrojovy obrazek
 * @param dst - Cilovy obrazek (vstupuje do funkce jako nealokovany)
 * @return Error code
 */
extern int FORMATTER_formatToBMP8(Image *src, Image **dst);

/**
 * @brief Zmeni format libovolneho obrazku na BMP 24b
 * @param src - Zdrojovy obrazek
 * @param dst - Cilovy obrazek (vstupuje do funkce jako nealokovany)
 * @return Error code
 */
extern int FORMATTER_formatToBMP24(Image *src, Image **dst);

#endif // FORMATTER_H
