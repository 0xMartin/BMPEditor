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
    layout->setSpacing(0);

    // tabulka pro BMP file header
    this->fileHeaderTable = createTable();
    setupTable(this->fileHeaderTable);

    // tabulka pro BMP info header
    this->infoHeaderTable = createTable();
    setupTable(this->infoHeaderTable);

    // color paleta
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *colorPaletteWidged = new QWidget();
    scrollArea->setWidget(colorPaletteWidged);
    this->colorPalette = new QGridLayout(this);
    colorPaletteWidged->setLayout(this->colorPalette);

    // pridani tabulke do hlavni layoutu tohoto widgetu
    this->fileHeaderLabel = this->createHeader("File Header");
    layout->addWidget(this->fileHeaderLabel);
    layout->addWidget(this->fileHeaderTable);
    this->infoHeaderLabel = this->createHeader("BMP Info Header");
    layout->addWidget(this->infoHeaderLabel);
    layout->addWidget(this->infoHeaderTable);
    this->colorsLabel = this->createHeader("Color Palette");
    layout->addWidget(this->colorsLabel);
    layout->addWidget(scrollArea);
    setLayout(layout);
}

QLabel * ImageInfoPanel::createHeader(const QString &name) {
    QLabel * label = new QLabel(name);
    QFont font = label->font();
    font.setBold(true);
    font.setPointSize(14);
    label->setFont(font);
    label->setStyleSheet("background-color: rgb(39, 39, 41); padding: 6px");
    return label;
}

QTableWidget* ImageInfoPanel::createTable() {
    QTableWidget *table = new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(2);
    table->horizontalHeader()->setStretchLastSection(true);
    return table;
}

void ImageInfoPanel::setupTable(QTableWidget *table) {
    QTableWidgetItem *headerItem1 = new QTableWidgetItem("Name");
    QFont font = headerItem1->font();
    font.setBold(true);
    headerItem1->setFont(font);
    headerItem1->setBackground(Qt::lightGray);
    headerItem1->setFlags(headerItem1->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *headerItem2 = new QTableWidgetItem("Value");
    font = headerItem2->font();
    font.setBold(true);
    headerItem2->setFont(font);
    headerItem2->setBackground(Qt::lightGray);
    headerItem2->setFlags(headerItem2->flags() & ~Qt::ItemIsEditable);

    table->setHorizontalHeaderItem(0, headerItem1);
    table->setHorizontalHeaderItem(1, headerItem2);
}

void ImageInfoPanel::addRow(QTableWidget *table, const QString &fieldName, const QString &value) {
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(fieldName));
    table->setItem(row, 1, new QTableWidgetItem(value));
}

void ImageInfoPanel::setImage(Image *img) {
    // clear
    for (int i = this->infoHeaderTable->rowCount() - 1; i >= 0; --i) {
        this->infoHeaderTable->removeRow(i);
    }
    for (int i = this->fileHeaderTable->rowCount() - 1; i >= 0; --i) {
        this->fileHeaderTable->removeRow(i);
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
        this->fileHeaderLabel->setText("File Header");
        buffer = (char)(bmp->bmpFileHeader.type & 0xFF);
        buffer += (char)((bmp->bmpFileHeader.type >> 8) & 0xFF);
        this->addRow(this->fileHeaderTable, "Type", buffer);
        this->addRow(this->fileHeaderTable, "Size", QString::number(bmp->bmpFileHeader.size));
        this->addRow(this->fileHeaderTable, "Reserved1", "0x" + QString::number(bmp->bmpFileHeader.reserved1, 16));
        this->addRow(this->fileHeaderTable, "Reserved2", "0x" + QString::number(bmp->bmpFileHeader.reserved2, 16));
        this->addRow(this->fileHeaderTable, "Offset", "0x" + QString::number(bmp->bmpFileHeader.offset, 16));

        // info header
        this->infoHeaderLabel->setText("BMP Info Header");
        this->addRow(this->infoHeaderTable, "Size", QString::number(bmp->bmpInfoHeader.size));
        this->addRow(this->infoHeaderTable, "Width", QString::number(bmp->bmpInfoHeader.width));
        this->addRow(this->infoHeaderTable, "Height", QString::number(bmp->bmpInfoHeader.height));
        this->addRow(this->infoHeaderTable, "Planes", QString::number(bmp->bmpInfoHeader.planes));
        this->addRow(this->infoHeaderTable, "BitCount", QString::number(bmp->bmpInfoHeader.bitCount));
        this->addRow(this->infoHeaderTable, "Compression", QString::number(bmp->bmpInfoHeader.compression));
        this->addRow(this->infoHeaderTable, "ImageSize", QString::number(bmp->bmpInfoHeader.imageSize));
        this->addRow(this->infoHeaderTable, "XPixelsPerMeter", QString::number(bmp->bmpInfoHeader.xPixelsPerMeter));
        this->addRow(this->infoHeaderTable, "YPixelsPerMeter", QString::number(bmp->bmpInfoHeader.yPixelsPerMeter));
        this->addRow(this->infoHeaderTable, "ColorsUsed", QString::number(bmp->bmpInfoHeader.colorsUsed));
        this->addRow(this->infoHeaderTable, "ColorsImportant", QString::number(bmp->bmpInfoHeader.colorsImportant));

        // paleta barev
        this->colorsLabel->setText("Color Palette");
        if(bmp->bmpInfoHeader.bitCount <= 8 && bmp->bmpInfoHeader.bitCount > 0) {
            int row = 0;
            int col = 0;
            for (int i = 0; i < (1 << bmp->bmpInfoHeader.bitCount); ++i) {
                RGBQUAD color = bmp->bmpColors[i];
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

        this->repaint();
    }
}
