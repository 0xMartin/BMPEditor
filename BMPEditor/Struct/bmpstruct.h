#ifndef BITMAPFILEHEADER_H
#define BITMAPFILEHEADER_H

#include <cstdint>

/**
 * @brief Struktura pro hlavicku souboru BMP
 */
struct BitMapFileHeader {
    uint16_t type;  /** Oznaceni souboru (Musí byt 'BM' pro BMP soubory) */
    uint32_t size;  /** Velikost celeho souboru v bytech */
    uint16_t reserved1; /** Rezervovana hodnota 1 */
    uint16_t reserved2; /** Rezervovana hodnota 2 */
    uint32_t offset;    /** Offset datove oblasti od zacatku souboru */
};

/**
 * @brief Struktura pro informace o BMP obrazku
 */
struct BitMapInfoHeader {
    uint32_t size;          /** Velikost hlavicky (40 bytu) */
    int32_t width;          /** Sirka obrazku v pixelech */
    int32_t height;         /** Vyska obrazku v pixelech */
    uint16_t planes;        /** Pocet barevnych rovin (vzdy 1) */
    uint16_t bitCount;      /** Pocet bitu na pixel (typicky 24 pro 24-bitove obrazky) */
    uint32_t compression;   /** Typ komprese (vetsinou 0 pro zadnou kompresi) */
    uint32_t imageSize;     /** Velikost datove oblasti v bytech */
    int32_t xPixelsPerMeter; /** Horizontalni rozliseni v pixelech na metr */
    int32_t yPixelsPerMeter; /** Vertikalni rozliseni v pixelech na metr */
    uint32_t colorsUsed;    /** Pocet pouzitych barev v palete (0 znamena maximalni mozny pocet) */
    uint32_t colorsImportant; /** Pocet "dulezitych" barev (0 znamena vsechny barvy jsou dulezite) */
};

/**
 * @brief Validator struktur BMP souboru
 * @param fileHeader - Struktura BitMapFileHeader
 * @param infoHeader - Struktura BitMapInfoHeader
 * @return Error Code
 */
extern int BMP_STRUCT_validate(const BitMapFileHeader & fileHeader, const BitMapInfoHeader & infoHeader);

#endif // BITMAPFILEHEADER_H
