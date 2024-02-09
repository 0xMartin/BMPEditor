#ifndef BMPIO_H
#define BMPIO_H

#include <QString>
#include "../Struct/bmpstruct.h"
#include "types.h"

/**
 * @brief Funkce pro nacitani BMP obrazku ze souboroveho systemu
 * @param path - Cesta k souboru kde se nachazi BMP obrazek (in)
 * @param fileHeader - Reference na hlacivkou souboru, ze ktereho bude obrazek nacitan (out)
 * @param infoHeader - Reference na hlavicku BMP obrazku (out)
 * @param palette - Pointer na paletu barev (out)
 * @param data - Obrazova data, ktere budou nacitani ze souboru (out)
 * @return Error code
 */
extern int BMP_IO_loadBMPImage(const QString & path,
                               BitMapFileHeader & fileHeader,
                               BitMapInfoHeader & infoHeader,
                               RGBQUAD ** palette,
                               unsigned char ** data);

/**
 * @brief Funkce pro ulozeni BMP obrazku
 * @param path - Cesta k souboru do ktereho bude obrazek ulozen (in)
 * @param fileHeader - Reference na hlacivkou souboru, ze ktereho bude obrazek nacitan (in)
 * @param infoHeader - Reference na hlavicku BMP obrazku (in)
 * @param data - Obrazova data, ktere budou zapsana do souboru (in)
 * @return Error code
 */
extern int BMP_IO_saveBMPImage(const QString & path,
                               const BitMapFileHeader & fileHeader,
                               const BitMapInfoHeader & infoHeader,
                               const RGBQUAD * palette,
                               const unsigned char * data);

#endif // BMPIO_H
