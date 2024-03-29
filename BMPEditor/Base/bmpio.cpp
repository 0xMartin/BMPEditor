#include "bmpio.h"

#include <QFile>
#include <QDebug>

#include "../Base/error.h"

/******************************************************************************************************************************************/
// FUNCTION DEFINITION
/******************************************************************************************************************************************/

int BMP_IO_loadBMPImage(const QString &path,
                        BitMapFileHeader_t &fileHeader,
                        BitMapInfoHeader_t &infoHeader,
                        RGBQUAD_t **palette,
                        unsigned char **pixels) {
    if(palette == NULL || pixels == NULL) {
        return ERR_NULL_PTR;
    }

    // soubor ze ktereho bude nacitan BMP obrazke (binarni cteni)
    //std::ifstream file(path.toStdString(), std::ios::binary);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return ERR_FILE_OPEN;
    }
    qDebug() << "BMP LOAD - file opened";

    // precte ze souboru hlavicky souboru a BMP obrazku
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitMapFileHeader_t));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitMapInfoHeader_t));
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
        uint16_t paletteSize = 1 << infoHeader.bitCount;
        // alokace palety barev
        if(*palette != NULL) {
            delete[] *palette;
        }
        *palette = new RGBQUAD_t[paletteSize];
        if(*palette == NULL) {
            file.close();
            return ERR_ALLOC;
        }
        // nacteni palety barev do pole "RGBQUAD" (blue, greeb, red, reserved)
        file.read(reinterpret_cast<char*>(*palette), paletteSize * sizeof(RGBQUAD_t));
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
    uint32_t stride = BMP_IO_calculateStride(infoHeader.bitCount, infoHeader.width);
    qDebug() << "BMP LOAD - stride size: " << stride;

    // nacteni vsech pixelu obrazku z data bufferu
    file.seek(fileHeader.offset);
    uint32_t index = 0;
    uint32_t offset = 0;
    RGBQUAD_t color;
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
                        const BitMapFileHeader_t &fileHeader,
                        const BitMapInfoHeader_t &infoHeader,
                        const RGBQUAD_t *palette,
                        const unsigned char *pixels) {
    // overeni platnosti hlavicek
    int errorCode = BMP_STRUCT_validate(fileHeader, infoHeader);
    if (errorCode != STATUS_OK) {
        return errorCode;
    }
    qDebug() << "BMP SAVE - header validated";

    // ovevre soubor pro zapis dat
    //std::ofstream file(path.toStdString(), std::ios::binary);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return ERR_FILE_OPEN;
    }
    qDebug() << "BMP SAVE - file opened";

    //zapis hlavicek
    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BitMapFileHeader_t));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BitMapInfoHeader_t));
    qDebug() << "BMP SAVE - headers writing done";

    // zapis palety barev
    uint16_t paletteSize = 0;
    if (infoHeader.bitCount <= 8) {
        // vypocet velikosti palety
        paletteSize = 1 << infoHeader.bitCount;
        file.write(reinterpret_cast<const char*>(palette), paletteSize * sizeof(RGBQUAD_t));
        qDebug() << "BMP SAVE - color palette writing done ( " << paletteSize << " )";
    }

    // vypocet stride
    uint32_t stride = BMP_IO_calculateStride(infoHeader.bitCount, infoHeader.width);
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
                colorIndex = RGB_findColorIndex(palette,
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

    // flush
    file.flush();

    // overeni zda data byli spravne zapsany
    if (file.error() != QFile::NoError) {
        qDebug() << "BMP write to file error:" << file.errorString();
        file.close();
        return ERR_FILE_WRITE;
    }

    file.close();

    return STATUS_OK;
}

uint32_t BMP_IO_calculateStride(uint8_t bitCount, uint16_t width)
{
    uint32_t stride = bitCount * width;
    if (stride % 32 != 0)
        stride = (stride | 31) + 1;
    stride /= 8;
    return stride;
}
