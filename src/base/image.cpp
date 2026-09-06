#include "image.h"

#include "error.h"
#include <filesystem>
#include <QDebug>
#include <QFile>
#include <QImageReader>

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

int Image::importImage(const QString &filePath)
{
    // overeni existence souboru
    if (!QFile::exists(filePath)) {
        qDebug() << "File not exists: " << filePath;
        return ERR_FILE_OPEN;
    }

    // image reader
    QImageReader reader(filePath);

    // nacteni informaci o obrazku
    QSize imageSize = reader.size();

    // nastaveni vlastnosti obrazku
    this->imgPath = filePath;
    this->width = imageSize.width();
    this->height = imageSize.height();
    this->bitDepth = 24;

    // nacteni obrazku do pameti
    QImage image = reader.read();
    if (image.isNull()) {
        qDebug() << "IMAGE read error: " << reader.errorString();
        return ERR_FILE_READ;
    }

    // konverze formatu na RGB (pokud tomu tak jeste neni)
    if (image.format() != QImage::Format_RGB888) {
        image = image.convertToFormat(QImage::Format_RGB888);
    }

    // kopirovani dat z QImage do Image
    this->dataLen = this->width * this->height * 3;
    this->pixels = new unsigned char[this->dataLen];
    int index, x;
    QRgb rgb;
    for (int y = 0; y < this->height; ++y) {
        for (x = 0; x < this->width; ++x) {
            rgb = image.pixel(x, y);
            index = ((this->height - y - 1) * this->width + x) * 3;
            this->pixels[index] = qRed(rgb);
            this->pixels[index + 1] = qGreen(rgb);
            this->pixels[index + 2] = qBlue(rgb);
        }
    }

    return STATUS_OK;
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
    QRgb rgb;
    int index, x;
    for (int y = 0; y < this->height; ++y) {
        for (x = 0; x < this->width; ++x) {
            index = ((height - y - 1) * width + x) * 3;
            rgb = qRgb(pixels[index], pixels[index + 1], pixels[index + 2]);
            this->imagePreview->setPixel(x, y, rgb);
        }
    }
    return STATUS_OK;
}
