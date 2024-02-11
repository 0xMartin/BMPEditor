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

    // vykresli histogram RGB
    float barWidth = (float)width() / histogramRed.size();
    int maxHeight = maxFrequency;

    float x;
    float height;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    for (size_t i = 0; i < histogramRed.size(); ++i) {
        x = (float)i * barWidth;
        height = histogramRed[i] * this->height() / maxHeight;
        painter.drawRect(x, this->height() - height, (barWidth < 1 ? 1 : barWidth), height);
    }

    painter.setBrush(Qt::green);
    for (size_t i = 0; i < histogramGreen.size(); ++i) {
        x = (float)i * barWidth;
        height = histogramGreen[i] * this->height() / maxHeight;
        painter.drawRect(x, this->height() - height, (barWidth < 1 ? 1 : barWidth), height);
    }

    painter.setBrush(Qt::blue);
    for (size_t i = 0; i < histogramBlue.size(); ++i) {
        x = (float)i * barWidth;
        height = histogramBlue[i] * this->height() / maxHeight;
        painter.drawRect(x, this->height() - height, (barWidth < 1 ? 1 : barWidth), height);
    }
}

void ImageHistogramWidget::computeHistogram() {
    if (image->pixels == NULL) return;
    if (image->dataLen == 0) return;

    histogramRed.clear();
    histogramGreen.clear();
    histogramBlue.clear();
    histogramRed.resize(256, 0);
    histogramGreen.resize(256, 0);
    histogramBlue.resize(256, 0);
    maxFrequency = 0;

    for (size_t i = 0; i < image->dataLen; i += 3) {
        int r = (int)(image->pixels[i]);
        int g = (int)(image->pixels[i + 1]);
        int b = (int)(image->pixels[i + 2]);
        histogramRed[r]++;
        histogramGreen[g]++;
        histogramBlue[b]++;
        maxFrequency = std::max(maxFrequency, histogramRed[r]);
        maxFrequency = std::max(maxFrequency, histogramGreen[g]);
        maxFrequency = std::max(maxFrequency, histogramBlue[b]);
    }
}

void ImageHistogramWidget::updateDone()
{
    qDebug() << "Histogram update done";
    this->repaint();
}
