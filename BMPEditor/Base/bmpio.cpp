#include "bmpio.h"

#include <fstream>
#include <iostream>
#include <QDebug>

#include "../Base/error.h"

/**
 * @brief Najde index barvy v palete barev podle predanych argumentu funkce
 * @param palette - Ukazatel na paletu barev BMP obrazku
 * @param paletteSize - Velikost palety barev
 * @param red - Cervena slozka pixelu
 * @param green - Zelena slozka pixelu
 * @param blue - Modra slozka pixelu
 * @return Index barvy pixelu v palete barev (pokud neni barva primo nalezena tak barva s nejblizsi podobnosti)
 */
static inline int __findColorIndex(const RGBQUAD *palette, int paletteSize, int red, int green, int blue);

int BMP_IO_loadBMPImage(const QString &path,
                        BitMapFileHeader &fileHeader,
                        BitMapInfoHeader &infoHeader,
                        RGBQUAD **palette,
                        unsigned char **pixels) {
    if(palette == NULL || pixels == NULL) {
        return ERR_NULL_PTR;
    }

    // soubor ze ktereho bude nacitan BMP obrazke (binarni cteni)
    std::ifstream file(path.toStdString(), std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        return ERR_FILE_OPEN;
    }
    qDebug() << "BMP LOAD - file opened";

    // precte ze souboru hlavicky souboru a BMP obrazku
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitMapFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitMapInfoHeader));
    qDebug() << "BMP LOAD - header reading done";

    // overeni platnosti hlavicek
    int errorCode = BMP_STRUCT_validate(fileHeader, infoHeader);
    if (errorCode != STATUS_OK) {
        file.close();
        return errorCode;
    }
    qDebug() << "BMP LOAD - header validated";

    // pokud ma obrazek paletu barev (bitCount: 1, 2 nebo 8) tak ji ze souboru nacte
    if (infoHeader.bitCount <= 8) {
        // vypocet velikosti palety
        int paletteSize = 1 << infoHeader.bitCount;
        // alokace palety barev
        if(*palette != NULL) {
            delete[] *palette;
        }
        *palette = new RGBQUAD[paletteSize];
        if(*palette == NULL) {
            file.close();
            return ERR_ALLOC;
        }
        // nacteni palety barev do pole "RGBQUAD" (blue, greeb, red, reserved)
        file.read(reinterpret_cast<char*>(*palette), paletteSize * sizeof(RGBQUAD));
        qDebug() << "BMP LOAD - color palette loaded ( " << paletteSize << " )";
    }

    // alokace/realokace pole pixelu BMP obrazku (velikos = width * height * 3B)
    if(*pixels != NULL) {
        delete[] *pixels;
    }
    uint32_t pixArrSiz = infoHeader.width * infoHeader.height * 3;
    *pixels = new unsigned char[pixArrSiz];
    if (*pixels == NULL) {
        file.close();
        return ERR_ALLOC;
    }
    qDebug() << "BMP LOAD - image pixel array allocated (" << pixArrSiz << ")";

    // vypocet stride (musi byt dorovnany na 32b, posledni bity jsou 0)
    file.seekg(fileHeader.offset);
    uint16_t stride = infoHeader.bitCount * infoHeader.width;
    if (stride % 32 != 0)
        stride = (stride | 31) + 1;
    stride /= 8;
    qDebug() << "BMP LOAD - stride size: " << stride;

    // nacteni vsech pixelu obrazku z data bufferu
    uint32_t index = 0;
    uint32_t offset = 0;
    RGBQUAD color;
    int32_t x;
    unsigned char * buff = new unsigned char[stride];
    for (int32_t y = 0; y < infoHeader.height; ++y) {
        // nacte cely radek z obrazku
        file.read(reinterpret_cast<char*>(buff), stride);
        // precte vsechny pixely v radku obrazku
        offset = 0;
        for (x = 0; x < infoHeader.width; ++x) {
            // ziskani barvy pixelu
            switch (infoHeader.bitCount) {
            case 1:
                // pro 1b je index v palete vypocitan postupnym posouvanim masky "10000000". Jak se maska dostane nakonec,
                // prejde se k dalsimu uchar v poli. Vysledna hodnota po aplikaci masky "&" musi byt nasledne zpetne shiftnuta
                // na realnou hodnotu v useku teto masky
                color = (*palette)[(buff[offset / 8] & (0b10000000 >> offset % 8)) >> (7 - (offset % 8))];
                break;
            case 4:
                // pro 4b je index v palete vypocitan postupnym posouvanim masky "11110000". Podobny princip jak pro 1b
                color = (*palette)[(buff[offset / 8] & (0b11110000 >> offset % 8)) >> ((offset + 4) % 8)];
                break;
            case 8:
                // pro 8b (uchar) hodnota odpovida indexu barvy v palete
                color = (*palette)[buff[offset / 8]];
                break;
            default:
                // pro 24b jeden B (uchar) odpovida jedne barevne slozce pixelu
                color.red = buff[2 + offset / 8];
                color.green = buff[1 + offset / 8];
                color.blue = buff[offset / 8];
                break;
            }
            // offsest v radku obrazku
            offset += infoHeader.bitCount;
            // zapis barvy pixelu do pole pixelu obrazku
            index = (y * infoHeader.width + x) * 3;
            (*pixels)[index] = color.red;
            (*pixels)[index + 1] = color.green;
            (*pixels)[index + 2] = color.blue;
        }
    }
    delete[] buff;
    file.close();
    qDebug() << "BMP LOAD - pixels loaded";

    return STATUS_OK;
}

int BMP_IO_saveBMPImage(const QString &path,
                        const BitMapFileHeader &fileHeader,
                        const BitMapInfoHeader &infoHeader,
                        const RGBQUAD *palette,
                        const unsigned char *pixels) {
    // overeni platnosti hlavicek
    int errorCode = BMP_STRUCT_validate(fileHeader, infoHeader);
    if (errorCode != STATUS_OK) {
        return errorCode;
    }
    qDebug() << "BMP SAVE - header validated";

    // ovevre soubor pro zapis dat
    std::ofstream file(path.toStdString(), std::ios::binary);
    if (!file.is_open()) {
        return ERR_FILE_OPEN;
    }
    qDebug() << "BMP SAVE - file opened";

    //zapis hlavicek
    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BitMapFileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BitMapInfoHeader));
    qDebug() << "BMP SAVE - headers writing done";

    // zapis palety barev
    int paletteSize = 0;
    if (infoHeader.bitCount <= 8) {
        // vypocet velikosti palety
        paletteSize = 1 << infoHeader.bitCount;
        file.write(reinterpret_cast<const char*>(palette), paletteSize * sizeof(RGBQUAD));
        qDebug() << "BMP SAVE - color palette writing done ( " << paletteSize << " )";
    }

    // vypocet stride
    uint16_t stride = infoHeader.bitCount * infoHeader.width;
    if (stride % 32 != 0)
        stride = (stride | 31) + 1;
    stride /= 8;
    qDebug() << "BMP SAVE - stride size: " << stride;

    // zapis dat obrazku (inverzni zpusob jak u cteni)
    uint32_t index = 0;
    uint32_t offset = 0;
    int8_t colorIndex;
    int32_t x;
    unsigned char * buff = new unsigned char[stride];
    for (int32_t y = 0; y < infoHeader.height; ++y) {
        // cely buffer resetuje, prepise 0x0
        for(int i = 0; i < stride; ++i) {
            buff[i] = 0x0;
        }
        // zapis jednoho radku pixelu obrazku do bufferu
        offset = 0;
        for (x = 0; x < infoHeader.width; ++x) {
            // vypocet indexu pixelu
            index = (y * infoHeader.width + x) * 3;
            // pokud jde o obrazek s color paletou tak si najde v palete index barvy aktualniho pixelu
            if(infoHeader.bitCount <= 8) {
                colorIndex = __findColorIndex(palette,
                                              paletteSize,
                                              pixels[index],
                                              pixels[index + 1],
                                              pixels[index + 2]);
            }
            // zapis pixelu do bufferu
            switch (infoHeader.bitCount) {
            case 1:
                // zapis RGB pixelu ve 1b formatu (vyuziva paletu barev)
                // index barvy
                buff[offset / 8] |= (colorIndex << (7 - (offset % 8))) & (0b10000000 >> offset % 8);
                break;
            case 4:
                // zapis RGB pixelu ve 4b formatu (vyuziva paletu barev)
                // index barvy
                buff[offset / 8] |= (colorIndex << ((offset + 4) % 8)) & (0b11110000 >> offset % 8);
                break;
            case 8:
                // zapis RGB pixelu ve 8b (1B) formatu (vyuziva paletu barev)
                // index barvy
                buff[offset / 8] = colorIndex;
                break;
            default:
                // zapis RGB pixelu ve 24b (3B) formatu
                // pozice f bufferu je dana offsetem, ten se meni po 24b, jelikoz jde o pole uchar (8b) tak po 3 indexech v poli
                buff[offset / 8] = pixels[index + 2]; // blue
                buff[offset / 8 + 1] = pixels[index + 1]; // green
                buff[offset / 8 + 2] = pixels[index]; // red
                break;
            }
            // offsest v radku obrazku
            offset += infoHeader.bitCount;
        }
        // zapis bufferu do souboru
        file.write(reinterpret_cast<char*>(buff), stride);
    }
    delete[] buff;
    qDebug() << "BMP image data writing done (" << infoHeader.width << "; " << infoHeader.height << ")";

    // overeni zda data byli spravne zapsany
    if (!file.good()) {
        return ERR_FILE_WRITE;
    }

    file.close();

    return STATUS_OK;
}

static inline int __findColorIndex(const RGBQUAD *palette, int paletteSize, int red, int green, int blue) {
    int closestIndex = 0;
    int closestDistance = std::numeric_limits<int>::max();
    for (int i = 0; i < paletteSize; ++i) {
        int distance = std::abs(palette[i].red - red) +
                       std::abs(palette[i].green - green) +
                       std::abs(palette[i].blue - blue);
        if (distance < closestDistance) {
            closestIndex = i;
            closestDistance = distance;
        }
    }
    return closestIndex;
}
