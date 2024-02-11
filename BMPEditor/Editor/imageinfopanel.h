#ifndef IMAGEINFOPANEL_H
#define IMAGEINFOPANEL_H

#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include "tablewidget.h"
#include "imagehistogramwidget.h"
#include "framewidget.h"
#include "../Base/image.h"


class ImageInfoPanel : public QWidget
{
public:
    explicit ImageInfoPanel(QWidget *parent = nullptr);

    void setImage(Image *img);
    void refresh();

protected:
    Image *image;

private:
    // aktivni zobrazovaci prvky
    ImageHistogramWidget *histogram;
    CustomTableWidget *fileHeaderTable;
    CustomTableWidget *infoHeaderTable;
    QGridLayout *colorPalette;

    // UI kontajner pro zobrazovaci prvky
    FrameWidget *histogramFrame;
    FrameWidget *fileTableFrame;
    FrameWidget *infoTableFrame;
    FrameWidget *colorPaletteFrame;
};

#endif // IMAGEINFOPANEL_H
