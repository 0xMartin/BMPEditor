#include "bmpimage.h"

#include "../Base/error.h"
#include "../Base/bmpio.h"
#include <QDebug>

BMPImage::BMPImage() : Image() {
    this->type = IMG_BMP;
    this->bmpColors = NULL;
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
                                        &this->pixels);

    // nastaveni parametru Image tridy
    if (errorCode == STATUS_OK) {
        this->dataLen = this->bmpInfoHeader.width * this->bmpInfoHeader.height * 3;
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
    if (path.isEmpty()) {
        return BMP_IO_saveBMPImage(this->imgPath,
                                   this->bmpFileHeader,
                                   this->bmpInfoHeader,
                                   this->bmpColors,
                                   this->pixels);
    } else {
        // Pokud není cesta specifikována, použijte původní cestu k obrázku
        return BMP_IO_saveBMPImage(path,
                                   this->bmpFileHeader,
                                   this->bmpInfoHeader,
                                   this->bmpColors,
                                   this->pixels);
    }
}

void BMPImage::refresh()
{

}
