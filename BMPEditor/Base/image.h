#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <string.h>
#include <QString>
#include <QPainter>

#define MAX_IMG_PATH_LEN 512

/**
 * @brief Typ obrazku
 */
enum ImageType {
    IMG_NONE, IMG_BMP, IMG_PCX
};

/**
 * @brief Rodicovska trida resteroveho obrazku. Vsechny ostatni tridy obrazku dedi od teto tridy.
 */
class Image
{
protected:
    QImage *imagePreview; /** Vykreslovany obrazek */

    /**
     * @brief Vygeneruje nahled obrazku
     * @return Error code
     */
    int buildImagePreview();

public:
    QString imgPath; /** Puvodni cesta k nactenemu obrazku */
    ImageType type; /** Typo obrazku */

    uint8_t bitDepth; /** Bitova hloubka - pocet bitu na jeden pixel */
    size_t dataLen; /** Delka pole pixelu obrazku */
    size_t width; /** Sirka obrazku v pixelech  */
    size_t height; /** Vyska obrazku v pixelech  */
    unsigned char * data; /** Pole pixelu obrazu */

    // Konstruktor & Destruktor tridy image
    Image();
    ~Image();

    /**
     * @brief Virtualni metoda urcena pro nacteni obrazku.
     * @param path - Ceska k obrazku, ktery bude do aplikace nacten
     * @return Error code
     */
    virtual int loadImage(const QString & path);

    /**
     * @brief Virtualni funkce pro ulozeni obrazku.
     * @param path - Cesta kde bude obrazek v systemu ulozen (volitelny parametr, pokud nebude pouzit tak se obrazek ulozi na sve puvodni misto)
     * @return Error code
     */
    virtual int saveImage(const QString & path = "");

    /**
     * @brief Virtualni funkce pro kopirovani obrazku.
     * @param img - Obrazek, ze ktereho budou data kopirovany
     * @return Error code
     */
    virtual int copyImage(Image img);

    /**
     * @brief Event pro vykresleni obrazku
     * @param painter - QPainter
     */
    virtual void paintEvent(QPainter &painter);

    /**
     * @brief Navrati nazev obrazku
     * @return Nazev obrazku
     */
    QString getName() const;

};

#endif // IMAGE_H
