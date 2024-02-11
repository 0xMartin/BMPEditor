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
 * @param pixels - Obrazova data, ktere budou nacitani ze souboru (out)
 * @return Error code
 */
extern int BMP_IO_loadBMPImage(const QString & path,
                               BitMapFileHeader & fileHeader,
                               BitMapInfoHeader & infoHeader,
                               RGBQUAD ** palette,
                               unsigned char ** pixels);

/**
 * @brief Funkce pro ulozeni BMP obrazku. Vyzaduje mit pripravene a validni struktury BMP file & info a pole pixelu obrazku + color paleta.
 * @param path - Cesta k souboru do ktereho bude obrazek ulozen (in)
 * @param fileHeader - Reference na hlacivkou souboru, ze ktereho bude obrazek nacitan (in)
 * @param infoHeader - Reference na hlavicku BMP obrazku (in)
 * @param palette - Pointer na paletu barev. Vyzadaovano je pri bitove hloubce: 1, 4 nebo 8 (in)
 * @param pixels - Obrazova data, ktere budou zapsana do souboru (in)
 * @return Error code
 */
extern int BMP_IO_saveBMPImage(const QString & path,
                               const BitMapFileHeader & fileHeader,
                               const BitMapInfoHeader & infoHeader,
                               const RGBQUAD * palette,
                               const unsigned char * pixels);

/**
 * @brief Vypocet velikosti stride v BMP obrazku. Bity v radku obrazku musi byt zarovnani na 32b, koncove nevyuzite bity jsou 0.
 * @param bitCount - Pocet bitu na jeden pixel v BMP obrazku
 * @param width - Sirka obrazku v pixelech
 * @return Velikost stride
 */
extern uint16_t BMP_IO_calculateStride(uint8_t bitCount, uint16_t width);

/**
 * @brief Najde index barvy v palete barev podle predanych argumentu funkce
 * @param palette - Ukazatel na paletu barev BMP obrazku
 * @param paletteSize - Velikost palety barev
 * @param red - Cervena slozka pixelu
 * @param green - Zelena slozka pixelu
 * @param blue - Modra slozka pixelu
 * @return Index barvy pixelu v palete barev (pokud neni barva primo nalezena tak barva s nejblizsi podobnosti)
 */
extern uint16_t BMP_IO_findColorIndex(const RGBQUAD *palette, uint16_t paletteSize, uint8_t red, uint8_t green, uint8_t blue);

#endif // BMPIO_H
