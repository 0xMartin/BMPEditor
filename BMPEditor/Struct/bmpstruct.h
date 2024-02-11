#ifndef BITMAPFILEHEADER_H
#define BITMAPFILEHEADER_H

#include <cstdint>

// zarovnani struktur na 1b (velmi dulezite!!)
#pragma pack(push, 1)

/**
 * @brief Struktura pro hlavicku souboru BMP
 */
struct BitMapFileHeader_t {
    uint16_t type {0x4D42};  /** Oznaceni souboru (Musí byt 'BM' pro BMP soubory) */
    uint32_t size {0};  /** Velikost celeho souboru v bytech */
    uint16_t reserved1 {0}; /** Rezervovana hodnota 1 */
    uint16_t reserved2 {0}; /** Rezervovana hodnota 2 */
    uint32_t offset {0};    /** Offset datove oblasti od zacatku souboru */
};

/**
 * @brief Struktura pro informace o BMP obrazku
 */
struct BitMapInfoHeader_t {
    uint32_t size {0};          /** Velikost hlavicky (40 bytu) */
    int32_t width {0};          /** Sirka obrazku v pixelech */
    int32_t height {0};         /** Vyska obrazku v pixelech */
    uint16_t planes {1};        /** Pocet barevnych rovin (vzdy 1) */
    uint16_t bitCount {0};      /** Pocet bitu na pixel (typicky 24 pro 24-bitove obrazky) */
    uint32_t compression {0};   /** Typ komprese (vetsinou 0 pro zadnou kompresi) */
    uint32_t imageSize {0};     /** Velikost datove oblasti v bytech */
    int32_t xPixelsPerMeter {0}; /** Horizontalni rozliseni v pixelech na metr */
    int32_t yPixelsPerMeter {0}; /** Vertikalni rozliseni v pixelech na metr */
    uint32_t colorsUsed {0};    /** Pocet pouzitych barev v palete (0 znamena maximalni mozny pocet) */
    uint32_t colorsImportant {0}; /** Pocet "dulezitych" barev (0 znamena vsechny barvy jsou dulezite) */
};

#pragma pack(pop)

/**
 * @brief Validator struktur BMP souboru
 * @param fileHeader - Struktura BitMapFileHeader
 * @param infoHeader - Struktura BitMapInfoHeader
 * @return Error Code
 */
extern int BMP_STRUCT_validate(const BitMapFileHeader_t & fileHeader, const BitMapInfoHeader_t & infoHeader);

#endif // BITMAPFILEHEADER_H
