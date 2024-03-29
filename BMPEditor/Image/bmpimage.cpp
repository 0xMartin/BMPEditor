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

void BMPImage::update(ImageUpdateMode mode)
{
    // aktualizace vysky a sirky BMP obrazku
    bmpInfoHeader.width = (int32_t)(this->width);
    bmpInfoHeader.height = (int32_t)(this->height);

    // aktualizace pixelu podle color palety a prepocitani palety (provede se jen v pripade ze byla pozmenena barva v obrazku)
    if(mode == IMG_UPDATE_ALL || mode == IMG_UPDATE_COLOR) {
        if(bmpInfoHeader.bitCount <= 8) {
            uint16_t paletteSize = 1 << this->bmpInfoHeader.bitCount;

            // prepocitani color palety
            std::vector<RGBQUAD_t> colors = RGB_generateColorPalette(this->pixels, this->width, this->height, paletteSize);
            if(this->bmpColors != NULL) delete[] this->bmpColors;
            this->bmpColors = new RGBQUAD_t[colors.size()];
            if(this->bmpColors == NULL) return;
            std::copy(colors.begin(), colors.end(), this->bmpColors);

            // aktualizace pixelu
            RGBQUAD_t rgb;
            uint16_t index;
            for(uint32_t i = 0; i < this->dataLen; i += 3) {
                // ziskani barvy aktualniho pixele
                rgb.red = this->pixels[i];
                rgb.green = this->pixels[i + 1];
                rgb.blue = this->pixels[i + 2];
                // urci index barvy v palete barev, ktera je nejblize barve aktualniho pixelu
                index = RGB_findColorIndex(this->bmpColors, paletteSize, rgb.red, rgb.green, rgb.blue);
                // aktualnimu pixelu nastavi barvu z palety (aby barva pixelu odpovidala realite = bitove hloubce)
                rgb = this->bmpColors[index];
                this->pixels[i] = rgb.red;
                this->pixels[i + 1] = rgb.green;
                this->pixels[i + 2] = rgb.blue;
            }
        }
    }
}

int BMPImage::copyImage(Image * img)
{
    if(img == NULL) {
        return ERR_NULL_PTR;
    }
    BMPImage *bmp = dynamic_cast<BMPImage *>(img);
    if(img == NULL) {
        return ERR_TYPE;
    }

    // kopirovani dat Image tridy
    bmp->imgPath = this->imgPath;
    bmp->type = this->type;
    bmp->bitDepth = this->bitDepth;
    bmp->dataLen = this->dataLen;
    bmp->width = this->width;
    bmp->height = this->height;

    // kopirovani hlavicek BMP
    bmp->bmpFileHeader = this->bmpFileHeader;
    bmp->bmpInfoHeader = this->bmpInfoHeader;

    // kopirovani palety barev (pokud je k dispozici: 1, 4 a 8)
    if(bmpInfoHeader.bitCount <= 8) {
        int paletteSize = 1 << this->bmpInfoHeader.bitCount;
        bmp->bmpColors = new RGBQUAD_t[paletteSize];
        if(std::copy(this->bmpColors, this->bmpColors + paletteSize, bmp->bmpColors) == NULL) {
            return ERR_MEM_CPY;
        }
    }

    // kopirovani pixelu obrazku
    bmp->pixels = new unsigned char[this->dataLen];
    if(std::copy(this->pixels, this->pixels + this->dataLen, bmp->pixels) == NULL) {
        return ERR_MEM_CPY;
    }

    return STATUS_OK;
}

Image *BMPImage::cloneImage()
{
    BMPImage *bmp = new BMPImage();
    if(bmp != NULL) {
        this->copyImage(bmp);
    }
    return bmp;
}

int BMPImage::isBMPImage(Image *img, int bitDepth) {
    if(img == NULL)
        return ERR_NULL_PTR;
    if (img->type == IMG_BMP) {
        BMPImage *bmp = dynamic_cast<BMPImage *>(img);
        if(bmp != NULL)
            if(bmp->bmpInfoHeader.bitCount == bitDepth)
                return ERR_SAME_FORMAT;
    }
    return STATUS_OK;
}

int BMPImage::importAsBMP24(const QString &path)
{
    // nacteni obrazovych dat do rodicovske tridy
    int errCode = Image::importImage(path);
    if(errCode != STATUS_OK) {
        return errCode;
    }

    // vypocet stride ve finalnim BMP obrazku
    uint32_t stride = BMP_IO_calculateStride(24, this->width);

    // nastaveni typu obrazku
    this->type = IMG_BMP;

    // file header
    this->bmpFileHeader.type = 0x4D42;
    this->bmpFileHeader.size = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t) + (stride * this->height);
    this->bmpFileHeader.reserved1 = this->bmpFileHeader.reserved2 = 0;
    this->bmpFileHeader.offset = sizeof(BitMapFileHeader_t) + sizeof(BitMapInfoHeader_t);

    // info header
    this->bmpInfoHeader.size = sizeof(BitMapInfoHeader_t);
    this->bmpInfoHeader.width = this->width;
    this->bmpInfoHeader.height = this->height;
    this->bmpInfoHeader.planes = 1;
    this->bmpInfoHeader.bitCount = 24;
    this->bmpInfoHeader.compression = 0x0;
    this->bmpInfoHeader.imageSize = (stride * this->height);
    this->bmpInfoHeader.xPixelsPerMeter = 0x0;
    this->bmpInfoHeader.yPixelsPerMeter = 0x0;
    this->bmpInfoHeader.colorsUsed = 0;
    this->bmpInfoHeader.colorsImportant = 0;

    // sestaveni nahledu
    this->buildImagePreview();

    return STATUS_OK;
}
