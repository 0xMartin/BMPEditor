#include "imageutils.h"

ImageUtils::ImageUtils() {

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

}

void ImageUtils::rotateCounterClockwise()
{

}

void ImageUtils::flipVertically()
{

}

void ImageUtils::flipHorizontally()
{

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
