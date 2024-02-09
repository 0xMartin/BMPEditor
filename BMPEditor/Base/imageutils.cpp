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
