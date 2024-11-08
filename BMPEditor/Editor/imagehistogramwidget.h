#ifndef IMAGEHISTOGRAMWIDGET_H
#define IMAGEHISTOGRAMWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <vector>
#include "../Base/threadrunner.h"
#include "../Base/image.h"

// preciznost vykreslovani histogramu. Best = 1, Worst = 32
#define PRECISION 2

class ImageHistogramWidget : public QWidget {
    Q_OBJECT

public:
    explicit ImageHistogramWidget(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override {
        return QSize(100, 150);
    }

    void setImage(Image *img);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Image *image;

    ThreadRunner worker;

    std::vector<int> histogramRed;
    std::vector<int> histogramGreen;
    std::vector<int> histogramBlue;
    int zeroCount;
    int maxFrequency;

    void computeHistogram();

private slots:
    void updateDone();
};

#endif // IMAGEHISTOGRAMWIDGET_H
