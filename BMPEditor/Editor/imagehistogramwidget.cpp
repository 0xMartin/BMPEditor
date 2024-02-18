#include "imagehistogramwidget.h"

#include <algorithm>

ImageHistogramWidget::ImageHistogramWidget(QWidget *parent) : QWidget(parent) {
    this->image = NULL;
}

void ImageHistogramWidget::setImage(Image *img) {
    this->image = img;
    if (this->image != NULL) {
        computeHistogram();
    }
    qDebug() << "Histogram run update in separated thread";
    worker.runInThread([&]() {
        this->update();
        QMetaObject::invokeMethod(this, "updateDone", Qt::QueuedConnection);
    });
}

void ImageHistogramWidget::paintEvent(QPaintEvent *event) {
    if (this->image == NULL) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(52, 52, 56));
    painter.drawRect(0, 0, this->width(), this->height());

    // vypocet barWidth a maxHeight
    size_t numColumns = histogramRed.size();
    float barWidth = (float)width() / numColumns;
    int maxHeight = maxFrequency;

    // vykresli histogram RGB
    int step = PRECISION;
    qDebug() << this->zeroCount;
    if(this->zeroCount >= 128)
        // zvyseni presnosti pokud se v histogramu vyskytuje velike mnozstvi 0
        step = 1;

    // red
    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    float x, y;
    painter.setBrush(Qt::red);
    QPolygonF redCurve;
    redCurve.append(QPointF(0, this->height() - 1));
    for (size_t i = 0; i < histogramRed.size(); i += step) {
        x = (float)i * barWidth + barWidth / 2;
        y = this->height() - histogramRed[i] * this->height() / maxHeight;
        if (histogramRed[i] > 0 && x > 0 && x < this->width())
            redCurve.append(QPointF(x, y));
    }
    redCurve.append(QPointF(this->width() - 1, this->height() - 1));
    painter.drawPolygon(redCurve);

    // green
    painter.setBrush(Qt::green);
    QPolygonF greenCurve;
    greenCurve.append(QPointF(0, this->height() - 1));
    for (size_t i = 0; i < histogramGreen.size(); i += step) {
        x = (float)i * barWidth + barWidth / 2;
        y = this->height() - histogramGreen[i] * this->height() / maxHeight;
        if (histogramGreen[i] > 0 && x > 0 && x < this->width())
            greenCurve.append(QPointF(x, y));
    }
    greenCurve.append(QPointF(this->width() - 1, this->height() - 1));
    painter.drawPolygon(greenCurve);

    // blue
    painter.setBrush(Qt::blue);
    QPolygonF blueCurve;
    blueCurve.append(QPointF(0, this->height() - 1));
    for (size_t i = 0; i < histogramBlue.size(); i += step) {
        x = (float)i * barWidth + barWidth / 2;
        y = this->height() - histogramBlue[i] * this->height() / maxHeight;
        if (histogramBlue[i] > 0 && x > 0 && x < this->width())
            blueCurve.append(QPointF(x, y));
    }
    blueCurve.append(QPointF(this->width() - 1, this->height() - 1));
    painter.drawPolygon(blueCurve);

}

void ImageHistogramWidget::computeHistogram() {
    if (image->pixels == NULL) return;
    if (image->dataLen == 0) return;

    // clear predchoziho histogramu
    histogramRed.clear();
    histogramGreen.clear();
    histogramBlue.clear();
    histogramRed.resize(256, 0);
    histogramGreen.resize(256, 0);
    histogramBlue.resize(256, 0);

    // vypocet RGB histogramu
    maxFrequency = 0;
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    for (size_t i = 0; i < image->dataLen; i += 3) {
        int r = (int)(image->pixels[i]);
        int g = (int)(image->pixels[i + 1]);
        int b = (int)(image->pixels[i + 2]);
        histogramRed[r]++;
        histogramGreen[g]++;
        histogramBlue[b]++;
        maxR = std::max(maxR, histogramRed[r]);
        maxG = std::max(maxG, histogramGreen[g]);
        maxB = std::max(maxB, histogramBlue[b]);
    }
    maxFrequency = (int)((maxR + maxG + maxB) / 3.0);

    // spocita prumerny pocet nul v RGB histogramu
    this->zeroCount = 0;
    for(int i = 0; i < 256; ++i) {
        if(histogramRed[i] == 0) zeroCount++;
        if(histogramGreen[i] == 0) zeroCount++;
        if(histogramBlue[i] == 0) zeroCount++;
    }
    this->zeroCount /= 3;
}

void ImageHistogramWidget::updateDone()
{
    qDebug() << "Histogram update done";
    this->repaint();
}
