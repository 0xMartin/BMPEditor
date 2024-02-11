#include "imageinfopanel.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QLayoutItem>
#include <QFrame>
#include <QScrollArea>

#include "../Image/bmpimage.h"

ImageInfoPanel::ImageInfoPanel(QWidget *parent) : QWidget(parent) {
    // vertiklani layout pro prvky
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 4, 4, 3);

    // aktivni prvky *************************************************************

    // histogram
    this->histogram = new ImageHistogramWidget(this);

    // tabulka pro BMP file header
    this->fileHeaderTable = new CustomTableWidget(this);
    // tabulka pro BMP info header
    this->infoHeaderTable = new CustomTableWidget(this);

    // color paleta
    QScrollArea *scrollAreaColors = new QScrollArea(this);
    scrollAreaColors->setWidgetResizable(true);
    QWidget *colorPaletteWidged = new QWidget();
    scrollAreaColors->setWidget(colorPaletteWidged);
    this->colorPalette = new QGridLayout(this);
    colorPaletteWidged->setLayout(this->colorPalette);

    // UI kontajnery pro aktivni prvky ********************************************
    this->histogramFrame = new FrameWidget("Histogram", this->histogram, this);
    this->fileTableFrame = new FrameWidget("BMP File Header", this->fileHeaderTable, this);
    this->infoTableFrame = new FrameWidget("BMP Info Header", this->infoHeaderTable, this);
    this->colorPaletteFrame = new FrameWidget("Color Palette", scrollAreaColors, this);

    // pridani tabulke do hlavni layoutu tohoto widgetu
    layout->addWidget(this->histogramFrame);
    layout->addWidget(this->fileTableFrame);
    layout->addWidget(this->infoTableFrame);
    layout->addWidget(this->colorPaletteFrame);
    layout->addStretch();

    setLayout(layout);
}

void ImageInfoPanel::setImage(Image *img) {
    // clear
    for (int i = this->infoHeaderTable->getTable()->rowCount() - 1; i >= 0; --i) {
        this->infoHeaderTable->getTable()->removeRow(i);
    }
    for (int i = this->fileHeaderTable->getTable()->rowCount() - 1; i >= 0; --i) {
        this->fileHeaderTable->getTable()->removeRow(i);
    }
    QLayoutItem *item;
    while ((item = colorPalette->takeAt(0)) != nullptr) {
        colorPalette->removeItem(item);
        delete item->widget();
        delete item;
    }

    if(img == NULL) return;
    this->image = img;

    QString buffer = "";
    if(this->image->type == IMG_BMP) {
        BMPImage *bmp = (BMPImage*)img;

        // file header
        this->fileTableFrame->getLabel()->setText("BMP File Header");
        buffer = (char)(bmp->bmpFileHeader.type & 0xFF);
        buffer += (char)((bmp->bmpFileHeader.type >> 8) & 0xFF);
        this->fileHeaderTable->addRow("Type", buffer);
        this->fileHeaderTable->addRow("Size", QString::number(bmp->bmpFileHeader.size));
        this->fileHeaderTable->addRow("Reserved1", "0x" + QString::number(bmp->bmpFileHeader.reserved1, 16));
        this->fileHeaderTable->addRow("Reserved2", "0x" + QString::number(bmp->bmpFileHeader.reserved2, 16));
        this->fileHeaderTable->addRow("Offset", "0x" + QString::number(bmp->bmpFileHeader.offset, 16));

        // info header
        this->infoTableFrame->getLabel()->setText("BMP Info Header");
        this->infoHeaderTable->addRow("Size", QString::number(bmp->bmpInfoHeader.size));
        this->infoHeaderTable->addRow("Width", QString::number(bmp->bmpInfoHeader.width));
        this->infoHeaderTable->addRow("Height", QString::number(bmp->bmpInfoHeader.height));
        this->infoHeaderTable->addRow("Planes", QString::number(bmp->bmpInfoHeader.planes));
        this->infoHeaderTable->addRow("BitCount", QString::number(bmp->bmpInfoHeader.bitCount));
        this->infoHeaderTable->addRow("Compression", QString::number(bmp->bmpInfoHeader.compression));
        this->infoHeaderTable->addRow("ImageSize", QString::number(bmp->bmpInfoHeader.imageSize));
        this->infoHeaderTable->addRow("XPixelsPerMeter", QString::number(bmp->bmpInfoHeader.xPixelsPerMeter));
        this->infoHeaderTable->addRow("YPixelsPerMeter", QString::number(bmp->bmpInfoHeader.yPixelsPerMeter));
        this->infoHeaderTable->addRow("ColorsUsed", QString::number(bmp->bmpInfoHeader.colorsUsed));
        this->infoHeaderTable->addRow("ColorsImportant", QString::number(bmp->bmpInfoHeader.colorsImportant));

        // paleta barev
        this->colorPaletteFrame->getLabel()->setText("Color Palette");
        if(bmp->bmpInfoHeader.bitCount <= 8 && bmp->bmpInfoHeader.bitCount > 0) {
            int row = 0;
            int col = 0;
            for (int i = 0; i < (1 << bmp->bmpInfoHeader.bitCount); ++i) {
                RGBQUAD_t color = bmp->bmpColors[i];
                QFrame *colorFrame = new QFrame(this);
                colorFrame->setFrameShape(QFrame::Box);
                colorFrame->setFrameShadow(QFrame::Plain);
                colorFrame->setLineWidth(1);
                colorFrame->setFixedSize(22, 22);
                colorFrame->setToolTip(QString("RGB(%1, %2, %3)").arg(color.red).arg(color.green).arg(color.blue));
                colorFrame->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red).arg(color.green).arg(color.blue));
                colorPalette->addWidget(colorFrame, row, col);
                col++;
                if (col >= 7) {
                    col = 0;
                    row++;
                }
            }
        }

        this->histogramFrame->maximize();
        this->fileTableFrame->maximize();
        this->infoTableFrame->maximize();
        this->colorPaletteFrame->maximize();
        this->repaint();
    }

    // histogram
    this->histogram->setImage(this->image);
}

void ImageInfoPanel::refresh()
{
    if(this->image != NULL) {
        this->setImage(this->image);
    }
}
