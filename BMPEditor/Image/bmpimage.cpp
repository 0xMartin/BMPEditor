#include "bmpimage.h"

#include "../Base/error.h"
#include "../Base/bmpio.h"

BMPImage::BMPImage() : Image() {
    this->type = IMG_BMP;
    this->bmpColors = NULL;
    this->bmpFileHeader.type = 0x0;
    this->bmpFileHeader.offset = 0x0;
    this->bmpFileHeader.reserved1 = 0x0;
    this->bmpFileHeader.reserved2 = 0x0;
    this->bmpFileHeader.size = 0x0;
    this->bmpInfoHeader.size = 0x0;
    this->bmpInfoHeader.width = 0x0;
    this->bmpInfoHeader.height = 0x0;
    this->bmpInfoHeader.planes = 0x0;
    this->bmpInfoHeader.bitCount = 0x0;
    this->bmpInfoHeader.compression = 0x0;
    this->bmpInfoHeader.imageSize = 0x0;
    this->bmpInfoHeader.xPixelsPerMeter = 0x0;
    this->bmpInfoHeader.yPixelsPerMeter = 0x0;
    this->bmpInfoHeader.colorsUsed = 0x0;
    this->bmpInfoHeader.colorsImportant = 0x0;
}

BMPImage::~BMPImage() {
    if(this->bmpColors != NULL) {
        delete this->bmpColors;
    }
}

int BMPImage::loadImage(const QString & path) {
    this->imgPath = path;

    // nacte bmp obrazek pomoci funkce pro nacitani BMP obrazku
    int errorCode = BMP_IO_loadBMPImage(this->imgPath,
                                        this->bmpFileHeader,
                                        this->bmpInfoHeader,
                                        &this->bmpColors,
                                        &this->data);

    // nastaveni parametru Image tridy
    if (errorCode == STATUS_OK) {
        this->dataLen = this->bmpInfoHeader.imageSize;
        this->width = this->bmpInfoHeader.width;
        this->height = this->bmpInfoHeader.height;
        this->bitDepth = this->bmpInfoHeader.bitCount;
    }

    // sestaveni nahledu obrazku
    Image::buildImagePreview();

    return errorCode;
}

int BMPImage::saveImage(const QString & path) {
    // ulozi obrazek
    if (path[0] != 0x0) {
        return BMP_IO_saveBMPImage(this->imgPath,
                                   this->bmpFileHeader,
                                   this->bmpInfoHeader,
                                   this->bmpColors,
                                   this->data);
    } else {
        // Pokud není cesta specifikována, použijte původní cestu k obrázku
        return BMP_IO_saveBMPImage(path,
                                   this->bmpFileHeader,
                                   this->bmpInfoHeader,
                                   this->bmpColors,
                                   this->data);
    }
}
