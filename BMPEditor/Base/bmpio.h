#ifndef BMPIO_H
#define BMPIO_H

#include <QString>
#include "../Struct/bmpstruct.h"
#include "rgb.h"

/**
 * @brief Funkce pro nacitani BMP obrazku ze souboroveho systemu
 * @param path - Cesta k souboru kde se nachazi BMP obrazek (in)
 * @param fileHeader - Reference na hlacivkou souboru, ze ktereho bude obrazek nacitan (out)
 * @param infoHeader - Reference na hlavicku BMP obrazku (out)
 * @param palette - Pointer na paletu barev (out)
 * @param pixels - Pixely obrazku, ktere budou nacitani ze souboru. Pixely budou zapsany ve formatu RGB 3*uint8 (out)
 * @return Error code
 */
extern int BMP_IO_loadBMPImage(const QString & path,
                               BitMapFileHeader_t & fileHeader,
                               BitMapInfoHeader_t & infoHeader,
                               RGBQUAD_t ** palette,
                               unsigned char ** pixels);

/**
 * @brief Funkce pro ulozeni BMP obrazku. Vyzaduje mit pripravene a validni struktury BMP file & info a pole pixelu obrazku + color paleta.
 * @param path - Cesta k souboru do ktereho bude obrazek ulozen (in)
 * @param fileHeader - Reference na hlacivkou souboru, ze ktereho bude obrazek nacitan (in)
 * @param infoHeader - Reference na hlavicku BMP obrazku (in)
 * @param palette - Pointer na paletu barev. Vyzadaovano je pri bitove hloubce: 1, 4 nebo 8 (in)
 * @param pixels - Pixely obrazku, ktere budou zapsana do souboru. Jsou ve formatu RGB 3*uint8 (in)
 * @return Error code
 */
extern int BMP_IO_saveBMPImage(const QString & path,
                               const BitMapFileHeader_t & fileHeader,
                               const BitMapInfoHeader_t & infoHeader,
                               const RGBQUAD_t * palette,
                               const unsigned char * pixels);

/**
 * @brief Vypocet velikosti stride v BMP obrazku. Bity v radku obrazku musi byt zarovnani na 32b, koncove nevyuzite bity jsou 0.
 * @param bitCount - Pocet bitu na jeden pixel v BMP obrazku
 * @param width - Sirka obrazku v pixelech
 * @return Velikost stride
 */
extern uint32_t BMP_IO_calculateStride(uint8_t bitCount, uint16_t width);

#endif // BMPIO_H

