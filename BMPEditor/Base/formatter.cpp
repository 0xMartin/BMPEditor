#include "formatter.h"

#include <QDebug>
#include "bmpio.h"
#include "error.h"
#include "../Image/bmpimage.h"

/******************************************************************************************************************************************/
// FUNCTION DECLARATION
/******************************************************************************************************************************************/

/**
 * @brief Univerzalni metoda pro formatovani tridy Image na format BMP (1, 4, 8) s paletou barev
 * @param src - Zdrojovy obrazek
 * @param dst - Cilovy obrazek (vstupuje do funkce jako nealokovany)
 * @param bitCount - Pocet bitu na jeden pixel (bitova hloubka)
 * @return Error Code
 */
static int FORMATTER_formatToBMPWithPalette(Image *src, Image **dst, uint8_t bitCount);

/******************************************************************************************************************************************/
// FUNCTION DEFINITION
/******************************************************************************************************************************************/

int FORMATTER_formatToBMP1(Image *src, Image **dst)
{
    return FORMATTER_formatToBMPWithPalette(src, dst, 1);
}

int FORMATTER_formatToBMP4(Image *src, Image **dst)
{
    return FORMATTER_formatToBMPWithPalette(src, dst, 4);
}

int FORMATTER_formatToBMP8(Image *src, Image **dst)
{
    return FORMATTER_formatToBMPWithPalette(src, dst, 8);
}

static int FORMATTER_formatToBMPWithPalette(Image *src, Image **dst, uint8_t bitCount) {
    if(dst == NULL) return ERR_NULL_PTR;
    if(bitCount != 1 && bitCount != 4 && bitCount != 8) return ERR_INVALID_BIT_DEPTH;

    // pokud je aktualni obrazek formatu BMP (1,4,8)b tak se zmena formatu provadet nebude
    int errCode = BMPImage::isBMPImage(src, bitCount);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    // vytvoreni instance BMP obrazku
    BMPImage * bmpOut = new BMPImage();
    if(bmpOut == NULL) return ERR_ALLOC;
    *dst = bmpOut;

    // nastaveni image rodicovske tridy
    bmpOut->type = IMG_BMP;
    bmpOut->imgPath = src->imgPath;
    bmpOut->width = src->width;
    bmpOut->height = src->height;
    bmpOut->dataLen = src->dataLen;
    bmpOut->bitDepth = bitCount;

    // vypocet stride
    uint32_t stride = BMP_IO_calculateStride(bmpOut->bitDepth, bmpOut->width);

    // number of colors
    uint16_t paletteSize = 1 << bitCount;

    // incializace BMP file header
    bmpOut->bmpFileHeader.type = 0x4D42; // 'BM'
    bmpOut->bmpFileHeader.size = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t) + (stride * bmpOut->height);
    bmpOut->bmpFileHeader.reserved1 = 0;
    bmpOut->bmpFileHeader.reserved2 = 0;
    bmpOut->bmpFileHeader.offset = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t) + (sizeof(RGBQUAD_t) * paletteSize);
    qDebug() << "FORMAT TO BMP " << bitCount << "b - file header init done";

    // incializace BMP info header
    bmpOut->bmpInfoHeader.size = sizeof(BitMapInfoHeader_t);
    bmpOut->bmpInfoHeader.width = bmpOut->width;
    bmpOut->bmpInfoHeader.height = bmpOut->height;
    bmpOut->bmpInfoHeader.planes = 1;
    bmpOut->bmpInfoHeader.bitCount = bitCount;
    bmpOut->bmpInfoHeader.compression = 0;
    bmpOut->bmpInfoHeader.imageSize = (stride * bmpOut->height);
    bmpOut->bmpInfoHeader.xPixelsPerMeter = 0;
    bmpOut->bmpInfoHeader.yPixelsPerMeter = 0;
    bmpOut->bmpInfoHeader.colorsUsed = paletteSize;
    bmpOut->bmpInfoHeader.colorsImportant = 0;
    qDebug() << "FORMAT TO BMP " << bitCount << "b - info header init done";

    // alokace pameti pro pixely obrazku
    bmpOut->dataLen = src->dataLen;
    bmpOut->pixels = new unsigned char[bmpOut->dataLen];
    if(bmpOut->pixels == NULL) return ERR_ALLOC;
    qDebug() << "FORMAT TO BMP " << bitCount << "b - pixel array alloc done";

    // generovani palety barev
    std::vector<RGBQUAD_t> colors = RGB_generateColorPalette(src->pixels, src->width, src->height, paletteSize);
    bmpOut->bmpColors = new RGBQUAD_t[colors.size()];
    if(bmpOut->bmpColors == NULL) return ERR_ALLOC;
    std::copy(colors.begin(), colors.end(), bmpOut->bmpColors);
    qDebug() << "FORMAT TO BMP " << bitCount << "b - color palette generating done";

    // kopirovani pixelu ze zdrojoveho do ciloveho obrazku (color palety). Pixelu jsou v teto fazi zapisovany
    // do abtraktni tridy image a vzdy ve formatu RGB 3x uint8_t. Az pri ukladani dochazi k usporadani bitu
    // ve spravnem formatu.
    RGBQUAD_t rgb;
    for(uint32_t i = 0; i < src->dataLen; i += 3) {
        // ziskani barvy aktualniho pixele
        rgb.red = src->pixels[i];
        rgb.green = src->pixels[i + 1];
        rgb.blue = src->pixels[i + 2];
        // urci index barvy v palete barev, ktera je nejblize barve aktualniho pixelu
        uint16_t index = RGB_findColorIndex(bmpOut->bmpColors, paletteSize, rgb.red, rgb.green, rgb.blue);
        // aktualnimu pixelu nastavi barvu z palety (aby barva pixelu odpovidala realite = bitove hloubce)
        rgb = bmpOut->bmpColors[index];
        bmpOut->pixels[i] = rgb.red;
        bmpOut->pixels[i + 1] = rgb.green;
        bmpOut->pixels[i + 2] = rgb.blue;
    }
    qDebug() << "FORMAT TO BMP " << bitCount << "b - pixel copy done";

    // vygenerovani nahledu obrazku
    bmpOut->buildImagePreview();

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
    bmp24->bitDepth = 24;

    // vypocet stride
    uint32_t stride = BMP_IO_calculateStride(bmp24->bitDepth, bmp24->width);

    // incializace BMP file header
    bmp24->bmpFileHeader.type = 0x4D42; // 'BM'
    bmp24->bmpFileHeader.size = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t) + (stride * bmp24->height);
    bmp24->bmpFileHeader.reserved1 = 0;
    bmp24->bmpFileHeader.reserved2 = 0;
    bmp24->bmpFileHeader.offset = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t);
    qDebug() << "FORMAT TO BMP 24 - file header init done";

    // incializace BMP info header
    bmp24->bmpInfoHeader.size = sizeof(BitMapInfoHeader_t);
    bmp24->bmpInfoHeader.width = bmp24->width;
    bmp24->bmpInfoHeader.height = bmp24->height;
    bmp24->bmpInfoHeader.planes = 1;
    bmp24->bmpInfoHeader.bitCount = 24;
    bmp24->bmpInfoHeader.compression = 0;
    bmp24->bmpInfoHeader.imageSize = (stride * bmp24->height);
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
