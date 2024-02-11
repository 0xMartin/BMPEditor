#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#define MAX_HISTORY_SIZE 32

#include "image.h"
#include <vector>
#include <QObject>
#include <QThread>
#include <functional>
#include "threadrunner.h"

#define IMG_UTIL_ASYNC(imgutils, func) imgutils.runOperationAsync([&]() {func;});

/**
 * @brief Trida umoznujici upravi bitmapoveho obrazku. Obsahuje sadu zakladnich funkci + historii uprav.
 */
class ImageUtils : public QObject
{
    Q_OBJECT
protected:
    ThreadRunner worker; /** Vlakno umoznujici asynchronni vykonavani operaci */

    Image * currentImage; /** Obrazek ze kterym se aktualne pracuje */
    uint16_t historyIndex; /** Index v historii (urceno pro pohybovani v historii) */
    std::vector<Image*> imageHistory; /** Histrie obrazku */

    void refreshImage(const QString &message);
    void clearHistory();

public:
    explicit ImageUtils(QObject * parrent = nullptr);
    ~ImageUtils();

    // aktualni obrazek se kterym se pracuje
    Image * getCurrentImage() const;
    void setCurrentImage(Image * image);

    // historie
    uint16_t getHistoryIndex() const;
    std::vector<Image *> getImageHistory() const;

    /**
     * @brief Spusti libovolnou funkci asynchronne. Urceno pro pouziti tranformacnich funkci teto tridy.
     * @param func - Funkce, ktera ma byt vykonana v separatnim vlakne
     */
    void runOperationAsync(std::function<void()> func);

    // history

    /**
     * @brief Krok zpet v historii
     */
    void undo();

    /**
     * @brief Krok vpred v historii
     */
    void redo();

    // transformace

    /**
     * @brief Rotace od 90 stupnu po smeru hodinovych rucicek
     */
    void rotateClockwise();

    /**
     * @brief Rotace od 90 stupnu proti smeru hodinovych rucicek
     */
    void rotateCounterClockwise();

    /**
     * @brief Prevraceni obrazku ve vertikalni ose
     */
    void flipVertically();

    /**
     * @brief Prevraceni obrazku v horizontalni ose
     */
    void flipHorizontally();

    // filtry

    /**
     * @brief Aplikuje na obrazek grayscale filtr
     */
    void applyGrayscaleFilter();

    /**
     * @brief Aplikuje na obrazek filtr inverze barev
     */
    void applyInvertFilter();

    /**
     * @brief Aplikuje na obrazek sepia filtr
     */
    void applySepiaFilter();

    /**
     * @brief Aplikuje na obrazek filtr Gausova rozostreni
     */
    void applyBlurFilter(int radius);

    /**
     * @brief Zmena svetlosti obrazku
     */
    void applyBrightnessAdjustment(int value);

    /**
     * @brief Zmena kontrastu obrazku
     */
    void applyContrastAdjustment(double factor);

private slots:
    void workerJobFinished();

signals:
    void imageChangedSignal(const QString &message);
    void jobStart();
    void jobFinished();

};

#endif // IMAGEUTILS_H
