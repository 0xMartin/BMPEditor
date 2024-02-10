#ifndef IMAGEINFOPANEL_H
#define IMAGEINFOPANEL_H

#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include "tablewidget.h"
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
    QLabel *colorsLabel;
    CustomTableWidget *fileHeaderTable;
    CustomTableWidget *infoHeaderTable;
    QGridLayout *colorPalette;

    QLabel * createHeader(const QString &name);
};

#endif // IMAGEINFOPANEL_H
