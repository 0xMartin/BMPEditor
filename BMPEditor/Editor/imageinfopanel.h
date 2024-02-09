#ifndef IMAGEINFOPANEL_H
#define IMAGEINFOPANEL_H

#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include "../Base/image.h"

class ImageInfoPanel : public QWidget
{
public:
    explicit ImageInfoPanel(QWidget *parent = nullptr);

    void setImage(Image *img);

protected:
    Image *image;

private:
    QLabel *fileHeaderLabel;
    QLabel *infoHeaderLabel;
    QLabel *colorsLabel;
    QTableWidget *fileHeaderTable;
    QTableWidget *infoHeaderTable;
    QGridLayout *colorPalette;

    QLabel * createHeader(const QString &name);
    QTableWidget * createTable();
    void setupTable(QTableWidget *table);
    void addRow(QTableWidget *table, const QString &fieldName, const QString &value);


};

#endif // IMAGEINFOPANEL_H
