#include "bmpio.h"

#include <fstream>
#include <iostream>

#include "../Base/error.h"

int BMP_IO_loadBMPImage(const QString &path,
                        BitMapFileHeader &fileHeader,
                        BitMapInfoHeader &infoHeader,
                        RGBQUAD **palette,
                        unsigned char **data) {
    if(palette == NULL || data == NULL) {
        return ERR_NULL_PTR;
    }

    // soubor ze ktereho bude nacitan BMP obrazke (binarni cteni)
    std::ifstream file(path.toStdString(), std::ios::binary);
    if (!file.is_open()) {
        return ERR_FILE_OPEN;
    }

    // precte ze souboru hlavicky souboru a BMP obrazku
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitMapFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitMapInfoHeader));

    // overeni platnosti hlavicek
    int errorCode = BMP_STRUCT_validate(fileHeader, infoHeader);
    if (errorCode != STATUS_OK) {
        return errorCode;
    }

    // pokud ma obrazek paletu barev (bitCount: 1, 2 nebo 8) tak ji ze souboru nacte
    if (infoHeader.bitCount <= 8) {
        // vypocet velikosti palety
        int paletteSize = 1 << infoHeader.bitCount;
        // alokace palety barev
        *palette = new RGBQUAD[paletteSize];
        if(palette == NULL) {
            return ERR_ALLOC;
        }
        // nacteni palety barev do pole "RGBQUAD" (blue, greeb, red, reserved)
        file.read(reinterpret_cast<char*>(palette), paletteSize * sizeof(RGBQUAD));
    }

    // alokace datoveho pole BMP obrazku
    size_t dataSize = infoHeader.width * infoHeader.height * (infoHeader.bitCount / 8);
    *data = new unsigned char[dataSize];
    if (*data == nullptr) {
        return ERR_ALLOC;
    }

    //preste data BMP obrazku
    file.read(reinterpret_cast<char*>(*data), dataSize);

    // overi zda byl nacten spravny pocet bitu
    if (file.gcount() != static_cast<std::streamsize>(dataSize)) {
        delete[] *data;
        return ERR_FILE_READ;
    }

    // nacteni pixelu s vyuzitim color pallety (pokud je k dispozici)
    if (infoHeader.bitCount <= 8) {
        for (size_t i = 0; i < dataSize; ++i) {
            (*data)[i] = (*palette)[(*data)[i]].blue;
        }
    }

    return STATUS_OK;
}

int BMP_IO_saveBMPImage(const QString &path,
                        const BitMapFileHeader &fileHeader,
                        const BitMapInfoHeader &infoHeader,
                        const RGBQUAD *palette,
                        const unsigned char *data) {

    // ovevre soubor pro zapis dat
    std::ofstream file(path.toStdString(), std::ios::binary);
    if (!file.is_open()) {
        return ERR_FILE_OPEN;
    }

    //zapis hlavicek
    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BitMapFileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BitMapInfoHeader));

    // zapis palety barev
    if (infoHeader.bitCount <= 8) {
        // vypocet velikosti palety
        int paletteSize = 1 << infoHeader.bitCount;
        file.write(reinterpret_cast<const char*>(&palette), paletteSize * sizeof(RGBQUAD));
    }

    // zapis dat obrazku
    file.write(reinterpret_cast<const char*>(data), infoHeader.imageSize);

    // overeni zda data byli spravne zapsany
    if (!file.good()) {
        return ERR_FILE_WRITE;
    }

    return STATUS_OK;
}
