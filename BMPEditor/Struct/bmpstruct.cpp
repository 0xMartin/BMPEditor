#include "bmpstruct.h"

#include "../Base/error.h"

#include <QDebug>
#include "../Base/rgb.h"

/******************************************************************************************************************************************/
// FUNCTION DEFINITION
/******************************************************************************************************************************************/

int BMP_STRUCT_validate(const BitMapFileHeader_t& fileHeader, const BitMapInfoHeader_t& infoHeader) {
    // debug info
    qDebug() << "VALIDATE - BMP Type: " << "0x" + QString::number(fileHeader.type, 16);
    qDebug() << "VALIDATE - BMP Offset: " << fileHeader.offset;
    qDebug() << "VALIDATE - BMP File Header size: " << sizeof(BitMapFileHeader_t);
    qDebug() << "VALIDATE - BMP Info Header size: " << infoHeader.size;
    qDebug() << "VALIDATE - BMP bit count: " << infoHeader.bitCount;
    qDebug() << "VALIDATE - BMP compression: " << infoHeader.compression;
    qDebug() << "VALIDATE - BMP width: " << infoHeader.width;
    qDebug() << "VALIDATE - BMP height: " << infoHeader.height;
    qDebug() << "VALIDATE - BMP image size: " << infoHeader.imageSize;

    // overeni platnost hlavicky souboru
    if (fileHeader.type != 0x4D42) { // 'BM' v ASCII
        return ERR_INVALID_FILE_TYPE;
    }
    int paletteTotalSize = 0;
    if(infoHeader.bitCount <= 8) {
        paletteTotalSize = (1 << infoHeader.bitCount) * sizeof(RGBQUAD_t);
    }
    if (fileHeader.offset != sizeof(BitMapFileHeader_t) + infoHeader.size + paletteTotalSize) {
        return ERR_INVALID_FILE_OFFSET;
    }

    // overeni platnost hlavicky BMP obrazku
    if (infoHeader.size != 40) {
        return ERR_INVALID_BMP_HEADER_SIZ;
    }
    if (infoHeader.bitCount != 24 &&
        infoHeader.bitCount != 8 &&
        infoHeader.bitCount != 4 &&
        infoHeader.bitCount != 1) {
        return ERR_INVALID_BMP_BITS_PER_PIXEL;
    }
    if (infoHeader.compression != 0) {
        return ERR_UNSUPPORTED_BMP_COMPRESSION;
    }
    if (infoHeader.width <= 0 || infoHeader.height <= 0) {
        return ERR_INVALID_BMP_SIZE;
    }

    return STATUS_OK;
}
