#include "imageutils.h"

ImageUtils::ImageUtils(Image image) {

}

Image ImageUtils::getCurrentImage() const
{
    return currentImage;
}

void ImageUtils::setCurrentImage(const Image &newCurrentImage)
{
    currentImage = newCurrentImage;
}
