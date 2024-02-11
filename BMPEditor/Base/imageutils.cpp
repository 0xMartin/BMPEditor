#include "imageutils.h"

#include <QDebug>

ImageUtils::ImageUtils(QObject * parrent) : QObject(parrent) {
    this->historyIndex = 0;
    connect(&this->worker, &ThreadRunner::jobFinished, this, &ImageUtils::workerJobFinished);
}

ImageUtils::~ImageUtils()
{
    this->clearHistory();
}

uint16_t ImageUtils::getHistoryIndex() const
{
    return historyIndex;
}

std::vector<Image *> ImageUtils::getImageHistory() const
{
    return imageHistory;
}

void ImageUtils::runOperationAsync(std::function<void ()> func)
{
    emit this->jobStart();
    worker.runInThread(func);
}

void ImageUtils::refreshImage(const QString &message)
{
    if(this->currentImage == NULL) {
        emit imageChangedSignal("Failed to transform image");
    } else {
        // update image
        this->currentImage->refresh();
        this->currentImage->buildImagePreview();

        // odstrani vsechny obrazky z historie, ktere jsou za "historyIndex + 1"
        // (pokud historie za aktualne vybranym bodem pokracuje dale, a nyni je do
        // tohoto okaziku vlozena zmena, tak nasledujici kroky po tomtu uz musi byt
        // odstraneni, jelikoz jsou z neplatneny timto krokem vlozeni)
        for (size_t i = historyIndex + 1; i < imageHistory.size(); ++i) {
            qDebug() << "HISTORY clear image at: " << i;
            delete imageHistory[i];
        }
        imageHistory.erase(imageHistory.begin() + historyIndex + 1, imageHistory.end());

        // vlozi obrazek do historie
        if(this->currentImage != NULL) {
            Image *imgCopy = this->currentImage->cloneImage();
            if(imgCopy != NULL) {
                this->imageHistory.push_back(imgCopy);
                this->historyIndex = this->imageHistory.size() - 1;
            }
        }

        // omezeni velikosti historie
        while(this->imageHistory.size() > MAX_HISTORY_SIZE) {
            delete this->imageHistory.front();
            this->imageHistory.erase(imageHistory.begin());
            this->historyIndex = this->imageHistory.size() - 1;
            qDebug() << "HISTORY limit exceeded - removing image at: 0";
        }

        // emitace signalu o zmene obrazku
        emit imageChangedSignal(message);
    }
}

void ImageUtils::clearHistory()
{
    for(Image * img : this->imageHistory) {
        if(img != NULL) {
            delete img;
        }
    }
    this->imageHistory.clear();
    qDebug() << "HISTORY clear";
}

Image * ImageUtils::getCurrentImage() const
{
    return this->currentImage;
}

void ImageUtils::setCurrentImage(Image * image)
{
    this->currentImage = image;
    this->clearHistory();
    if(this->currentImage != NULL) {
        Image *imgCopy = this->currentImage->cloneImage();
        if(imgCopy != NULL) {
            this->imageHistory.push_back(imgCopy);
            this->historyIndex = 0;
        }
    }
}

void ImageUtils::undo()
{
    if(this->currentImage != NULL) {
        int tmp = this->historyIndex;
        this->historyIndex = std::max(0, this->historyIndex - 1);
        if(tmp == this->historyIndex) {
            return;
        }
        qDebug() << "UNDO - load image with index: " << this->historyIndex;
        Image *img = this->imageHistory.at(this->historyIndex);
        if(img != NULL) {
            img->copyImage(this->currentImage);
            this->currentImage->buildImagePreview();
            emit imageChangedSignal("Undo [" + QString::number(this->historyIndex) + "]");
        }
    }
}

void ImageUtils::redo()
{
    if(this->currentImage != NULL) {
        int tmp = this->historyIndex;
        this->historyIndex = std::min((uint16_t)(this->imageHistory.size()) - 1, this->historyIndex + 1);
        if(tmp == this->historyIndex) {
            return;
        }
        qDebug() << "REDO - load image with index: " << this->historyIndex;
        Image *img = this->imageHistory.at(this->historyIndex);
        if(img != NULL) {
            img->copyImage(this->currentImage);
            this->currentImage->buildImagePreview();
            emit imageChangedSignal("Redo [" + QString::number(this->historyIndex) + "]");
        }
    }
}

void ImageUtils::rotateClockwise()
{
    if (!currentImage) return;
    qDebug() << "Transform: rotate +90";

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
    qDebug() << "Transform: rotate -90";

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
    qDebug() << "Transform: V flip";

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
    qDebug() << "Transform: H flip";

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
    if (!currentImage) return;
    qDebug() << "Filer: grayscale";

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t index = (y * currentImage->width + x) * 3;
            unsigned char grayValue = (currentImage->pixels[index] +
                                       currentImage->pixels[index + 1] +
                                       currentImage->pixels[index + 2]) / 3;
            currentImage->pixels[index] = grayValue;
            currentImage->pixels[index + 1] = grayValue;
            currentImage->pixels[index + 2] = grayValue;
        }
    }

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Grayscale filter applied");
}

void ImageUtils::applyInvertFilter() {
    if (!currentImage) return;
    qDebug() << "Filer: invert";

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t index = (y * currentImage->width + x) * 3;
            currentImage->pixels[index] = 255 - currentImage->pixels[index];
            currentImage->pixels[index + 1] = 255 - currentImage->pixels[index + 1];
            currentImage->pixels[index + 2] = 255 - currentImage->pixels[index + 2];
        }
    }

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Invert filter applied");
}

void ImageUtils::applySepiaFilter()
{
    if (!currentImage) return;
    qDebug() << "Filer: sepia";

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            size_t index = (y * currentImage->width + x) * 3;

            // prevedeni barvy aktualni pixelu pomoci matematicke trasformace
            int r = currentImage->pixels[index];
            int g = currentImage->pixels[index + 1];
            int b = currentImage->pixels[index + 2];

            int tr = (int)(0.393 * r + 0.769 * g + 0.189 * b);
            int tg = (int)(0.349 * r + 0.686 * g + 0.168 * b);
            int tb = (int)(0.272 * r + 0.534 * g + 0.131 * b);

            // omezeni rozsahu hodnot 0-255
            currentImage->pixels[index] = (int)(std::min(255, tr));
            currentImage->pixels[index + 1] = (int)(std::min(255, tg));
            currentImage->pixels[index + 2] = (int)(std::min(255, tb));
        }
    }

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Sepia filter applied");
}

void ImageUtils::applyBlurFilter(int radius)
{
    if (!currentImage || radius <= 0) return;
    qDebug() << "Filer: blur = " << radius;

    std::vector<unsigned char> blurredPixels(currentImage->dataLen);

    for (size_t y = 0; y < currentImage->height; ++y) {
        for (size_t x = 0; x < currentImage->width; ++x) {
            int rAcc = 0, gAcc = 0, bAcc = 0, count = 0;

            // pro kazdy pixel vypocita prumernou hodnotu jeho okoli
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // overeni zda je pixel jeste uvnitr obrazku
                    if (nx >= 0 && nx < (int)(currentImage->width) &&
                        ny >= 0 && ny < (int)(currentImage->height)) {
                        size_t index = (ny * currentImage->width + nx) * 3;
                        rAcc += currentImage->pixels[index];
                        gAcc += currentImage->pixels[index + 1];
                        bAcc += currentImage->pixels[index + 2];
                        ++count;
                    }
                }
            }

            // vypocte prumernou hodnotu a ulozi ji do noveho obrazku
            size_t index = (y * currentImage->width + x) * 3;
            count = count == 0 ? 1 : count;
            blurredPixels[index] = (unsigned char)(rAcc / count);
            blurredPixels[index + 1] = (unsigned char)(gAcc / count);
            blurredPixels[index + 2] = (unsigned char)(bAcc / count);
        }
    }

    // nahradi puvodni pixely rozmazanymi pixely
    std::copy(blurredPixels.begin(), blurredPixels.end(), currentImage->pixels);

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Blur filter applied");
}

void ImageUtils::applyBrightnessAdjustment(int value)
{
    if (!currentImage) return;
    qDebug() << "Filer: brightness = " << value;

    // upravi kazdy pixel obrazku
    for (size_t i = 0; i < currentImage->dataLen; ++i) {
        int newValue = currentImage->pixels[i] + value;

        // omezeni hodnoty barvy pixelu 0-255
        newValue = std::max(0, std::min(255, newValue));

        currentImage->pixels[i] = (unsigned char)(newValue);
    }

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Brightness adjustment applied");
}

void ImageUtils::applyContrastAdjustment(double value)
{
    if (!currentImage) return;
    qDebug() << "Filer: contrast = " << value;

    double factor = (259.0 * (value + 255.0)) / (255.0 * (259.0 - value));
    for (size_t i = 0; i < currentImage->dataLen; ++i) {
        // Pro každý pixel provede úpravu kontrastu
        int newValue = static_cast<int>(factor * (currentImage->pixels[i] - 128) + 128);
        // Omezí hodnotu na rozsah 0-255
        currentImage->pixels[i] = (unsigned char)(std::max(0, std::min(255, newValue)));
    }

    // refresh obrazku + emitovani signalu o zmene obrazku
    this->refreshImage("Contrast adjustment applied");
}

void ImageUtils::workerJobFinished()
{
    emit this->jobFinished();
}
