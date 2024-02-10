#include "image.h"

#include "error.h"
#include <filesystem>
#include <QDebug>

Image::Image() {
    this->type = IMG_NONE;
    this->imgPath = "";
    this->bitDepth = 0;
    this->dataLen = 0;
    this->width = 0;
    this->height = 0;
    this->pixels = NULL;
    this->imagePreview = NULL;
}

Image::~Image() {
    if(this->pixels != NULL) {
        delete this->pixels;
    }
}

int Image::loadImage(const QString & path) {
    return ERR_NOT_IMPLEMENTED;
}

int Image::saveImage(const QString & path) {
    return ERR_NOT_IMPLEMENTED;
}

void Image::paintEvent(QPainter &painter) {
    if(this->imagePreview != NULL) {
        painter.drawImage(0, 0, *this->imagePreview);
    }
}

QString Image::getName() const {
    std::filesystem::path path(this->imgPath.toStdString());
    std::string fileName = path.filename().string();
    return QString::fromStdString(fileName);
}

int Image::buildImagePreview()
{
    if(this->imagePreview != NULL) {
        delete this->imagePreview;
    }
    this->imagePreview = NULL;
    this->imagePreview = new QImage(width, height, QImage::Format_RGB888);
    if(this->imagePreview == NULL) {
        return ERR_ALLOC;
    }
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            int index = ((height - y - 1) * width + x) * 3;
            QRgb rgb = qRgb(pixels[index], pixels[index + 1], pixels[index + 2]);
            this->imagePreview->setPixel(x, y, rgb);
        }
    }
    return STATUS_OK;
}
