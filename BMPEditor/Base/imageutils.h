#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#define MAX_HISTORY_SIZE 32

#include "image.h"
#include <vector>

/**
 * @brief Trida umoznujici upravi rasteroveho obrazku. Obsahuje sadu zakladnich funkci + historii uprav.
 */
class ImageUtils
{
protected:
    Image currentImage;
    std::vector<Image> imageHistory;

public:
    ImageUtils(Image image);

    Image getCurrentImage() const;
    void setCurrentImage(const Image &newCurrentImage);
};

#endif // IMAGEUTILS_H
