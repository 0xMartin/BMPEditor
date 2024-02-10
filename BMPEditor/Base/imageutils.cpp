#include "imageutils.h"


ImageUtils::ImageUtils(QObject * parrent) : QObject(parrent) {

}

void ImageUtils::refreshImage(const QString &message)
{
    if(this->currentImage == NULL) {
        emit imageChangedSignal("Failed to transform image");
    } else {
        this->currentImage->buildImagePreview();
        this->currentImage->refresh();
        emit imageChangedSignal(message);
    }
}

Image * ImageUtils::getCurrentImage() const
{
    return this->currentImage;
}

void ImageUtils::setCurrentImage(Image * image)
{
    this->currentImage = image;
}

void ImageUtils::undo()
{

}

void ImageUtils::redo()
{

}

void ImageUtils::rotateClockwise()
{
    if (!currentImage) return;

    const size_t newWidth = currentImage->height;
    const size_t newHeight = currentImage->width;
    unsigned char *rotatedPixels = new unsigned char[newWidth * newHeight * 3];

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t oldIndex = (y * currentImage->width + x) * 3;
            size_t newIndex = ((currentImage->width - x - 1) * newWidth + y) * 3;
            std::copy_n(&currentImage->pixels[oldIndex], 3, &rotatedPixels[newIndex]);
        }
    }

    std::swap(currentImage->width, currentImage->height);
    this->currentImage->buildImagePreview();
    delete[] currentImage->pixels;
    currentImage->pixels = rotatedPixels;

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Image rotated clockwise");
}

void ImageUtils::rotateCounterClockwise()
{
    if (!currentImage) return;

    const size_t newWidth = currentImage->height;
    const size_t newHeight = currentImage->width;
    unsigned char *rotatedPixels = new unsigned char[newWidth * newHeight * 3];

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t oldIndex = (y * currentImage->width + x) * 3;
            size_t newIndex = (x * newWidth + (currentImage->height - y - 1)) * 3;
            std::copy_n(&currentImage->pixels[oldIndex], 3, &rotatedPixels[newIndex]);
        }
    }

    std::swap(currentImage->width, currentImage->height);
    delete[] currentImage->pixels;
    currentImage->pixels = rotatedPixels;

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Image rotated counterclockwise");
}

void ImageUtils::flipVertically()
{
    if (!currentImage) return;

    unsigned char *flippedPixels = new unsigned char[currentImage->dataLen];

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t oldIndex = (y * currentImage->width + x) * 3;
            size_t newIndex = ((currentImage->height - y - 1) * currentImage->width + x) * 3;
            std::copy_n(&currentImage->pixels[oldIndex], 3, &flippedPixels[newIndex]);
        }
    }

    delete[] currentImage->pixels;
    currentImage->pixels = flippedPixels;

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Image flipped vertically");
}

void ImageUtils::flipHorizontally()
{
    if (!currentImage) return;

    unsigned char *flippedPixels = new unsigned char[currentImage->dataLen];

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t oldIndex = (y * currentImage->width + x) * 3;
            size_t newIndex = (y * currentImage->width + (currentImage->width - x - 1)) * 3;
            std::copy_n(&currentImage->pixels[oldIndex], 3, &flippedPixels[newIndex]);
        }
    }

    delete[] currentImage->pixels;
    currentImage->pixels = flippedPixels;

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Image flipped horizontally");
}

void ImageUtils::applyGrayscaleFilter()
{

}

void ImageUtils::applyInvertFilter()
{

}

void ImageUtils::applySepiaFilter()
{

}

void ImageUtils::applyBlurFilter(int radius)
{

}

void ImageUtils::applyBrightnessAdjustment(int value)
{

}

void ImageUtils::applyContrastAdjustment(double factor)
{

}

void ImageUtils::formatToBMP1()
{

}

void ImageUtils::formatToBMP4()
{

}

void ImageUtils::formatToBMP8()
{

}

void ImageUtils::formatToBMP24()
{

}
