#include "formatter.h"

#include <QDebug>
#include "bmpio.h"
#include "error.h"
#include "../Image/bmpimage.h"

int FORMATTER_formatToBMP1(Image *src, Image **dst)
{
    if(dst == NULL) return ERR_NULL_PTR;

    // pokud je aktualni obrazek formatu BMP 1b tak se zmena formatu provadet nebude
    int errCode = BMPImage::isBMPImage(src, 1);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    return STATUS_OK;
}

int FORMATTER_formatToBMP4(Image *src, Image **dst)
{
    if(dst == NULL) return ERR_NULL_PTR;

    // pokud je aktualni obrazek formatu BMP 4b tak se zmena formatu provadet nebude
    int errCode = BMPImage::isBMPImage(src, 4);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    return STATUS_OK;
}

int FORMATTER_formatToBMP8(Image *src, Image **dst)
{
    if(dst == NULL) return ERR_NULL_PTR;

    // pokud je aktualni obrazek formatu BMP 8b tak se zmena formatu provadet nebude
    int errCode = BMPImage::isBMPImage(src, 8);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    // vytvoreni instance BMP obrazku
    BMPImage * bmp24 = new BMPImage();
    if(bmp24 == NULL) return ERR_ALLOC;
    *dst = bmp24;

    // nastaveni image rodicovske tridy
    bmp24->type = IMG_BMP;
    bmp24->imgPath = src->imgPath;
    bmp24->width = src->width;
    bmp24->height = src->height;
    bmp24->dataLen = src->dataLen;

    // vypocet stride
    uint16_t stride = BMP_IO_calculateStride(src->bitDepth, src->width);

    // number of colors
    uint16_t paletteSize = 1 << 8;

    // incializace BMP file header
    bmp24->bmpFileHeader.type = 0x4D42; // 'BM'
    bmp24->bmpFileHeader.size = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + (stride * src->height);
    bmp24->bmpFileHeader.reserved1 = 0;
    bmp24->bmpFileHeader.reserved2 = 0;
    bmp24->bmpFileHeader.offset = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + (sizeof(RGBQUAD) * paletteSize);
    qDebug() << "FORMAT TO BMP 8 - file header init done";

    // incializace BMP info header
    bmp24->bmpInfoHeader.size = sizeof(BitMapInfoHeader);
    bmp24->bmpInfoHeader.width = src->width;
    bmp24->bmpInfoHeader.height = src->height;
    bmp24->bmpInfoHeader.planes = 1;
    bmp24->bmpInfoHeader.bitCount = 24;
    bmp24->bmpInfoHeader.compression = 0;
    bmp24->bmpInfoHeader.imageSize = stride * src->height;
    bmp24->bmpInfoHeader.xPixelsPerMeter = 0;
    bmp24->bmpInfoHeader.yPixelsPerMeter = 0;
    bmp24->bmpInfoHeader.colorsUsed = 0;
    bmp24->bmpInfoHeader.colorsImportant = 0;
    qDebug() << "FORMAT TO BMP 8 - info header init done";

    // alokace pameti pro pixely obrazku
    bmp24->dataLen = src->dataLen;
    bmp24->pixels = new unsigned char[bmp24->dataLen];
    if(bmp24->pixels == NULL) return ERR_ALLOC;
    qDebug() << "FORMAT TO BMP 8 - pixel array alloc done";

    // generovani palety barev
    std::vector<RGBQUAD> colors = RGB_quantizeImage(src->pixels, src->width, src->height, paletteSize);
    bmp24->bmpColors = new RGBQUAD[colors.size()];
    if(bmp24->bmpColors == NULL) return ERR_ALLOC;
    std::copy(colors.begin(), colors.end(), bmp24->bmpColors);
    qDebug() << "FORMAT TO BMP 8 - color palette generating done";

    // kopirovani pixelu ze zdrojoveho do ciloveho obrazku
    // ..........................................
    qDebug() << "FORMAT TO BMP 8 - pixel copy done";

    // vygenerovani nahledu obrazku
    bmp24->buildImagePreview();

    return STATUS_OK;
}

int FORMATTER_formatToBMP24(Image *src, Image **dst)
{
    if(dst == NULL) return ERR_NULL_PTR;

    // pokud je aktualni obrazek formatu BMP 24b tak se zmena formatu provadet nebude
    int errCode = BMPImage::isBMPImage(src, 24);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    // vytvoreni instance BMP obrazku
    BMPImage * bmp24 = new BMPImage();
    if(bmp24 == NULL) return ERR_ALLOC;
    *dst = bmp24;

    // nastaveni image rodicovske tridy
    bmp24->type = IMG_BMP;
    bmp24->imgPath = src->imgPath;
    bmp24->width = src->width;
    bmp24->height = src->height;
    bmp24->dataLen = src->dataLen;

    // vypocet stride
    uint16_t stride = BMP_IO_calculateStride(src->bitDepth, src->width);

    // incializace BMP file header
    bmp24->bmpFileHeader.type = 0x4D42; // 'BM'
    bmp24->bmpFileHeader.size = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + (stride * src->height);
    bmp24->bmpFileHeader.reserved1 = 0;
    bmp24->bmpFileHeader.reserved2 = 0;
    bmp24->bmpFileHeader.offset = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader);
    qDebug() << "FORMAT TO BMP 24 - file header init done";

    // incializace BMP info header
    bmp24->bmpInfoHeader.size = sizeof(BitMapInfoHeader);
    bmp24->bmpInfoHeader.width = src->width;
    bmp24->bmpInfoHeader.height = src->height;
    bmp24->bmpInfoHeader.planes = 1;
    bmp24->bmpInfoHeader.bitCount = 24;
    bmp24->bmpInfoHeader.compression = 0;
    bmp24->bmpInfoHeader.imageSize = stride * src->height;
    bmp24->bmpInfoHeader.xPixelsPerMeter = 0;
    bmp24->bmpInfoHeader.yPixelsPerMeter = 0;
    bmp24->bmpInfoHeader.colorsUsed = 0;
    bmp24->bmpInfoHeader.colorsImportant = 0;
    qDebug() << "FORMAT TO BMP 24 - info header init done";

    // alokace pameti pro pixely obrazku
    bmp24->dataLen = src->dataLen;
    bmp24->pixels = new unsigned char[bmp24->dataLen];
    if(bmp24->pixels == NULL) return ERR_ALLOC;
    qDebug() << "FORMAT TO BMP 24 - pixel array alloc done";

    // kopirovani pixelu ze zdrojoveho do ciloveho obrazku
    memcpy(bmp24->pixels, src->pixels, bmp24->dataLen);
    qDebug() << "FORMAT TO BMP 24 - pixel copy done";

    // vygenerovani nahledu obrazku
    bmp24->buildImagePreview();

    return STATUS_OK;
}
