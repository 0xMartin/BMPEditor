#include "image.h"

#include "error.h"
#include <filesystem>

Image::Image() {
    this->type = IMG_NONE;
    this->imgPath = "";
    this->bitDepth = 0;
    this->dataLen = 0;
    this->width = 0;
    this->height = 0;
    this->data = NULL;
    this->imagePreview = NULL;
}

Image::~Image() {
    if(this->data != NULL) {
        delete this->data;
    }
}

int Image::loadImage(const QString & path) {
    return ERR_NOT_IMPLEMENTED;
}

int Image::saveImage(const QString & path) {
    return ERR_NOT_IMPLEMENTED;
}

int Image::copyImage(Image img) {
    if(this->data != NULL) return STATUS_OK;
    if(img.dataLen == 0) return ERR_EMPTY_IMG;

    // alokace datoveho pole obrazku
    this->dataLen = img.dataLen;
    this->data = new unsigned char[this->dataLen];
    if(this->data == NULL) {
        return ERR_ALLOC;
    }

    // kopirovani dat
    if(memcpy(this->data, img.data, img.dataLen * sizeof(unsigned char)) == NULL) return ERR_MEM_CPY;

    return STATUS_OK;
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
    this->imagePreview = new QImage(data, width, height, QImage::Format_RGB888);
    if(this->imagePreview == NULL) {
        return ERR_ALLOC;
    }
    return STATUS_OK;
}
