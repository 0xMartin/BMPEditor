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
    IMG_NONE,
    IMG_BMP
};

/**
 * @brief Zpusob updatu "zmeny" obrazku
 */
enum ImageUpdateMode {
    IMG_UPDATE_NONE, /** Bez zmeny */
    IMG_UPDATE_ALL, /** Zmena vsech parametru */
    IMG_UPDATE_SIZE, /** Zmena velikosti obrazku */
    IMG_UPDATE_COLOR /** Zmena barev v obrazku */
};

/**
 * @brief Abstraktni trida resteroveho obrazku. Vsechny ostatni tridy obrazku dedi od teto tridy.
 */
class Image
{
protected:
    QImage *imagePreview; /** Vykreslovany obrazek */

public:
    QString imgPath; /** Puvodni cesta k nactenemu obrazku */
    ImageType type; /** Typo obrazku */

    uint8_t bitDepth; /** Bitova hloubka - pocet bitu na jeden pixel */
    size_t dataLen; /** Delka pole pixelu obrazku */
    size_t width; /** Sirka obrazku v pixelech  */
    size_t height; /** Vyska obrazku v pixelech  */
    unsigned char * pixels; /** Pole pixelu obrazu */

    // Konstruktor & Destruktor tridy image
    Image();
    virtual ~Image();

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
     * @brief Abstraktni funkce pro kopirovani obrazku.
     * @param img - Obrazek, ze ktereho budou data kopirovany
     * @return Error code
     */
    virtual int copyImage(Image * img) = 0;

    /**
     * @brief Abstraktni funkce pro klonovani obrazku.
     * @return Naklonovany obrazek
     */
    virtual Image * cloneImage() = 0;

    /**
     * @brief Event pro vykresleni obrazku
     * @param painter - QPainter
     */
    virtual void paintEvent(QPainter &painter);

    /**
     * @brief Vygeneruje nahled obrazku (pro zobrazeni v editoru)
     * @return Error code
     */
    int buildImagePreview();

    /**
     * @brief Univerzalni metoda update. Vyuziti pro prepocitani internich atributu tridy.
     */
    virtual void update(ImageUpdateMode mode) = 0;

    /**
     * @brief Navrati nazev obrazku
     * @return Nazev obrazku
     */
    QString getName() const;

    /**
     * @brief Univerzalni metoda pro import libovolneho typu obrazku
     * @param filePath - Cesta k obrazku
     * @return Error code
     */
    int importImage(const QString &filePath);

};

#endif // IMAGE_H
