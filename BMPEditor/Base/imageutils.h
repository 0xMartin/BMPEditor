#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#define MAX_HISTORY_SIZE 32

#include "image.h"
#include <vector>
#include <QObject>

/**
 * @brief Trida umoznujici upravi bitmapoveho obrazku. Obsahuje sadu zakladnich funkci + historii uprav.
 */
class ImageUtils : public QObject
{
    Q_OBJECT
protected:
    Image * currentImage;
    std::vector<Image*> imageHistory;

public:
    explicit ImageUtils(QObject * parrent = nullptr);

    Image * getCurrentImage() const;
    void setCurrentImage(Image * image);

    // history
    void undo();
    void redo();

    // transformace
    void rotateClockwise();
    void rotateCounterClockwise();
    void flipVertically();
    void flipHorizontally();

    // filtry
    void applyGrayscaleFilter();
    void applyInvertFilter();
    void applySepiaFilter();
    void applyBlurFilter(int radius);
    void applyBrightnessAdjustment(int value);
    void applyContrastAdjustment(double factor);

    // zmena formatu
    void formatToBMP1();
    void formatToBMP4();
    void formatToBMP8();
    void formatToBMP24();

signals:
    void imageChangedSignal(const QString &message);
};

#endif // IMAGEUTILS_H
