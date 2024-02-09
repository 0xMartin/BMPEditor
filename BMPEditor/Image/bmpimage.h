#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "../Base/image.h"
#include "../Struct/bmpstruct.h"
#include "../Base/types.h"

class BMPImage : public Image
{
public:
    BitMapFileHeader bmpFileHeader; /** Datova struktura souboru */
    BitMapInfoHeader bmpInfoHeader; /** Datova struktura BMP obrazku */
    RGBQUAD *bmpColors; /** Paleta barev */

    // Konstruktor & Destruktor BMP obrazku
    BMPImage();
    ~BMPImage();

    // funkce pro nacitani a ukladani BMP obrazku
    virtual int loadImage(const QString & path);
    virtual int saveImage(const QString & path = "");
};

#endif // BMPIMAGE_H