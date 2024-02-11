#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "../Base/image.h"
#include "../Struct/bmpstruct.h"
#include "../Base/rgb.h"

class BMPImage : public Image
{
public:
    BitMapFileHeader_t bmpFileHeader; /** Datova struktura souboru */
    BitMapInfoHeader_t bmpInfoHeader; /** Datova struktura BMP obrazku */
    RGBQUAD *bmpColors; /** Paleta barev */

    // Konstruktor & Destruktor BMP obrazku
    BMPImage();
    ~BMPImage();

    // funkce pro nacitani a ukladani BMP obrazku
    virtual int loadImage(const QString & path) override;
    virtual int saveImage(const QString & path = "") override;

    // funkce pro prepocitani informaci v headeru (pri zmene obrazovych dat)
    virtual void refresh() override;

    // funkce pro klonovani
    virtual int copyImage(Image * img) override;
    virtual Image * cloneImage() override;

    // overeni formatu abstraktniho Image
    static int isBMPImage(Image *img, int bitDepth);
};

#endif // BMPIMAGE_H
