#include "workspace.h"

#include <chrono>
#include <QApplication>
#include <QPainter>
#include <QtMath>
#include <QScrollBar>
#include <QMenu>
#include <QColorDialog>
#include <QMessageBox>


// velikost useku meritka v pixelech
#define RULE_STEP_PX_MIN 80

// inverzni scale
#define INV_SCALE(scale) (1.0 / scale)

Workspace::Workspace(const Config_Workspace_t & config, QWidget *parent): QWidget(parent)
{
    this->config = config;
    this->image = NULL;
    this->scale = 1.0f;
    this->mouseHelper = MouseEventHelper(3);
    this->globalOffset = QPoint(0, 0);
    this->currentPos = QPoint(0, 0);
    this->pressPos = QPoint(0, 0);
    this->begin = std::chrono::steady_clock::now();
    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    this->setMinimumSize(QSize(400, 400));
    this->setBackgroundRole(QPalette::Base);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
}

Image *Workspace::getImage() const
{
    return image;
}

void Workspace::setImage(Image *newImage)
{
    image = newImage;
}

void Workspace::setDefaultScale()
{
    if(this->image == NULL) return;
    if(this->image->width > this->image->height) {
        this->setScale(this->width() * 0.8 / this->image->width);
    } else {
        this->setScale(this->scale = this->height() * 0.8 / this->image->height);
    }
    this->repaint();
}

void Workspace::setDefaultOffset()
{
    this->globalOffset = QPointF(0.0f, 0.0f);
}

void Workspace::setScale(float scale)
{
    // update scale
    if(scale <= 0.05) {
        scale = 0.05;
    } else if(scale > 40.0) {
        scale = 40.0;
    }
    this->scale = scale;
    this->scale -= (float)(qRound(this->scale * 100) % 5) / 100;
}

void Workspace::addScale(float diff)
{
    // update scale
    float f = this->scale + diff;
    if(f <= 0.05) {
        f = 0.05;
    } else if(f > 40.0 ) {
        f = 40.0;
    }
    this->scale = f;
    this->scale -= (float)(qRound(this->scale * 100) % 5) / 100;
    // update mouse helper
    this->mouseHelper.updateDistance(DEFAULT_MOUSE_HELPER_DIST * INV_SCALE(this->scale));
}

void Workspace::zoomIN()
{
    if(this->scale < 3) {
        this->addScale(0.05); // 5 %
    } else if(this->scale < 6) {
        this->addScale(0.2); // 20 %
    } else {
        this->addScale(0.4); // 40 %
    }
}

void Workspace::zoomOUT()
{
    if(this->scale < 3) {
        this->addScale(-0.05);
    } else if(this->scale < 6) {
        this->addScale(-0.2);
    } else {
        this->addScale(-0.4);
    }
}

float Workspace::getScale() const
{
    return this->scale;
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    switch (event->buttons()) {
    case Qt::MiddleButton:
        this->setCursor(Qt::ClosedHandCursor);
        break;
    }
}

void Workspace::mouseReleaseEvent(QMouseEvent *event)
{
    // release event -> pohyb workspace pomoci stredoveho tlacitka
    if(event->buttons() != Qt::MiddleButton) {
        this->mouseHelper.resetMove();
        // nastaveni zakladniho kurzoru
        this->setCursor(Qt::ArrowCursor);
    }
    this->repaint();
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    this->currentPos = event->pos();

    // lokalni paint request promenna
    bool paint = false;

    // pohyb workspace pomoci stredniho tlacitka mysi
    if(event->buttons() == Qt::MiddleButton) {
        // move event -> zmena offsetu workspace pomoci stredoveho tlacitka
        if(this->mouseHelper.processMoveEvent(event->pos())) {
            QPointF diff = this->mouseHelper.diffFromLastPos();
            this->globalOffset += diff * INV_SCALE(this->scale) * this->config.mouseSensitivity;
            paint = true;
        }
    }

    // pozdavek na vykreslovani (limitovano na max 50 fps)
    if(paint) {
        // fps limitation
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count() > 1000.0 / this->config.fps) {
            begin = now;
            this->repaint();
        }
    }
}

void Workspace::wheelEvent(QWheelEvent *event)
{
    double delta = event->angleDelta().x() + event->angleDelta().y();
    if (QApplication::keyboardModifiers().testFlag(Qt::AltModifier) == true) {
        // zoom in & zoom out
        if(delta > 0) {
            this->zoomIN();
        } else {
            this->zoomOUT();
        }
    } else if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == true) {
        // posun v horizontalni ose
        int diff = (event->angleDelta().y() > 0 ? 1 : -1) * this->width() / 14 * INV_SCALE(this->scale);
        int x = this->globalOffset.x() + diff;
        // TODO ... x limits
        this->globalOffset.setX(x);
    } else {
        // posun ve vertikalni ose
        int diff = (event->angleDelta().y() > 0 ? 1 : -1) * this->height() / 14 * INV_SCALE(this->scale);
        int y = this->globalOffset.y() + diff;
        // TODO ... y limits
        this->globalOffset.setY(y);
    }

    // jednotne vykreslovani (limitovano na max FPS z nastaveni)
    // fps limitation
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count() > 1000.0 / this->config.fps) {
        begin = now;
        this->repaint();
    }
}

void Workspace::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // vykresleni celkoveho pozadi wokspacu
    painter.fillRect(this->rect(), QBrush(QColor(37, 37, 37), Qt::SolidPattern));


    if(this->image != NULL) {

        // vypocet offsetu na stred celkove plochy workspacu
        QPoint offset(
            (this->width() - this->image->width * this->scale) / 2  + this->globalOffset.x() * this->scale,
            (this->height() - this->image->height * this->scale) / 2 + this->globalOffset.y() * this->scale
            );

        //-------OBRAZEK-------------------------
        painter.save();
        // aplikace offsetu
        painter.translate(offset);
        // aplikace scale
        painter.scale(this->scale, this->scale);
        // vykresleni obrazku
        this->image->paintEvent(painter);
        // vraceni zpet do puvodniho stavu
        painter.restore();
        // outline
        painter.setPen(Qt::black);
        painter.drawRect(offset.x(), offset.y(), this->image->width * this->scale, this->image->height * this->scale);
        //-------OBRAZEK-------------------------


        // pixel grid (jen kdyz je obrazek hodne priblizen)
        if(this->scale >= PIXEL_GRID_MIN_SCALE) {
            painter.setPen(QColor(100, 100, 100));
            int s_w = this->image->width * this->scale;
            int s_h = this->image->height * this->scale;
            for(float x = 0; (int)x < s_w; x += this->scale) {
                painter.drawLine(
                    offset.x() + x,
                    offset.y(),
                    offset.x() + x,
                    offset.y() + s_h);
            }
            for(float y = 0; (int)y < s_h; y += this->scale) {
                painter.drawLine(
                    offset.x(),
                    offset.y() + y,
                    offset.x() + s_w,
                    offset.y() + y);
            }
        }


        // vykresleni ramecku meritek
        painter.fillRect(26, 0, this->width(), 26, QBrush(QColor(50, 50, 50), Qt::SolidPattern));
        painter.fillRect(0, 26, 26, this->height(), QBrush(QColor(50, 50, 50), Qt::SolidPattern));
        painter.setFont(this->config.font);
        painter.setPen(QColor(150, 150, 150));


        // x osa meritko
        int scaled_size = this->image->width * this->scale;
        float step = RULE_STEP_PX_MIN;
        float sf;
        for(int d = 1; d <= 20; ++d)
        {
            sf = (float) scaled_size / d;
            if(sf < RULE_STEP_PX_MIN) {
                break;
            }
            if(this->image->width % d == 0) {
                step = sf;
            }
        }
        float px_step = this->image->width / ((float)scaled_size / step);
        float from_start_to_0 = qCeil(offset.x() / step);
        float px = -px_step * from_start_to_0;
        for(int x = offset.x() - step * from_start_to_0;
             x < this->width();
             x+= step, px += px_step) {
            painter.drawText(QPointF(x + 5, 18), QString::number(px, 'f', 0));
            painter.drawLine(x, 4, x, 22);
        }


        // y osa meritko
        scaled_size = this->image->height * this->scale;
        step = RULE_STEP_PX_MIN;
        for(int d = 1; d <= 20; ++d)
        {
            sf = (float) scaled_size / d;
            if(sf < RULE_STEP_PX_MIN) {
                break;
            }
            if(this->image->height % d == 0) {
                step = sf;
            }
        }
        px_step = this->image->height / ((float)scaled_size / step);
        from_start_to_0 = qCeil((float)offset.y() / step);
        QFontMetrics fm(this->config.font);
        px = -px_step * from_start_to_0;
        int i;
        QString num;
        for(int y = offset.y() - step * from_start_to_0;
             y < this->height();
             y+= step, px += px_step) {

            num = QString::number(px, 'f', 0);
            i = 0;
            for(QChar &c : num) {
                painter.drawText(QPointF(8, y + (i + 0.9) * (fm.height() - 4) + 5), c);
                ++i;
            }
            painter.drawLine(4, y, 22, y);
        }

        // stredovy ramecek meritek
        painter.fillRect(0, 0, 26, 26, QBrush(QColor(46, 46, 46), Qt::SolidPattern));


        // pozicni informace
        painter.fillRect(26, this->height() - 26, this->width(), 26, QBrush(QColor(45, 45, 45), Qt::SolidPattern));
        painter.setPen(QColor(210, 150, 150));
        QString buffer = "";
        // jmeno vrstvy
        buffer = this->image->getName();
        buffer = buffer.leftJustified(40, ' ') + " ";
        // zoom
        buffer += QString::number(this->scale * 100, 'f', 0) + "%";
        buffer = buffer.leftJustified(53, ' ') + " ";
        // pozice
        bool b;
        QPointF pos = this->calculateEventOffsetPosition(this->currentPos, b);
        buffer += "X: " + QString::number(pos.x(), 'f', 0) + " Y: " + QString::number(pos.y(), 'f', 0);
        buffer = buffer.leftJustified(75, ' ') + " ";
        // dx & dy
        pos = pos - this->pressPos;
        buffer += "DX: " + QString::number(pos.x(), 'f', 0) + " DY: " + QString::number(pos.y(), 'f', 0);
        buffer = buffer.leftJustified(89, ' ');
        // paint info
        painter.drawText(QPointF(40, this->height() - 9), buffer);
    }

}

QPointF Workspace::calculateEventOffsetPosition(const QPointF &pos, bool &outOfRange) const
{
    if(this->image == NULL) return QPointF(0.0f, 0.0f);

    // workspace center offset : (widget.size - project.size) / 2
    QPointF offset(-(this->width() - this->image->width * this->scale) / 2,
                   -(this->height() - this->image->height * this->scale) / 2);

    // mouse event offset
    offset += pos;

    // global offset
    offset -= this->globalOffset * this->scale;

    // vynasobit inverznim scale
    // nyni uz finalni pozice prepoctana na soradnice v projektu
    offset *= INV_SCALE(this->scale);

    // pokud je mimo kreslici plochu tak zneplatni hodnoty
    if(offset.x() < 0 || offset.y() < 0 || offset.x() > this->image->width || offset.y() > this->image->height) {
        outOfRange = true;
    } else {
        outOfRange = false;
    }

    return offset;
}

