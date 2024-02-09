#include "bmpstruct.h"

#include "../Base/error.h"

int BMP_STRUCT_validate(const BitMapFileHeader& fileHeader, const BitMapInfoHeader& infoHeader) {
    // overeni platnost hlavicky souboru
    if (fileHeader.type != 0x4D42) { // 'BM' v ASCII
        return ERR_INVALID_FILE_TYPE;
    }
    if (fileHeader.offset != sizeof(BitMapFileHeader) + infoHeader.size) {
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
    if (infoHeader.width <= 0 || infoHeader.height <= 0 || infoHeader.imageSize <= 0) {
        return ERR_INVALID_BMP_SIZE;
    }

    return STATUS_OK;
}
