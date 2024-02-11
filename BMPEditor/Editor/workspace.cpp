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
#define RULE_STEP_PX_MIN 120

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
    if(scale <= 0.02) {
        scale = 0.02;
    } else if(scale > 40.0) {
        scale = 40.0;
    }
    this->scale = scale;
    this->scale -= (float)(qRound(this->scale * 100) % 2) / 100;
}

void Workspace::addScale(float diff)
{
    // update scale
    float f = this->scale + diff;
    if(f <= 0.02) {
        f = 0.02;
    } else if(f > 40.0 ) {
        f = 40.0;
    }
    this->scale = f;
    this->scale -= (float)(qRound(this->scale * 100) % 2) / 100;
    // update mouse helper
    this->mouseHelper.updateDistance(DEFAULT_MOUSE_HELPER_DIST * INV_SCALE(this->scale));
}

void Workspace::zoomIN()
{
    if(this->scale < 1) {
        this->addScale(0.02); // 2 % <0 - 100%>
    } else if(this->scale < 3) {
        this->addScale(0.2); // 20 % <100 - 300%>
    } else if(this->scale < 6) {
        this->addScale(0.4); // 40 % <300 - 600%>
    } else {
        this->addScale(0.8); // 80 %
    }
}

void Workspace::zoomOUT()
{
    if(this->scale < 1) {
        this->addScale(-0.02);
    } else if(this->scale < 3) {
        this->addScale(-0.2);
    } else if(this->scale < 6) {
        this->addScale(-0.4);
    } else {
        this->addScale(-0.8);
    }
}

float Workspace::getScale() const
{
    return this->scale;
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    if(!this->isEnabled()) return;

    this->pressPos = event->pos();

    switch (event->buttons()) {
    case Qt::MiddleButton:
        this->setCursor(Qt::ClosedHandCursor);
        break;
    }
}

void Workspace::mouseReleaseEvent(QMouseEvent *event)
{
    if(!this->isEnabled()) return;

    // release event -> pohyb workspace pomoci stredoveho tlacitka
    if(event->buttons() != Qt::MiddleButton) {
        this->mouseHelper.resetMove();
        // nastaveni zakladniho kurzoru
        this->setCursor(Qt::ArrowCursor);
    }

    // repaint
    this->repaint();

    // ulozeni last press pozice
    this->lastPressPos = this->pressPos;
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    if(!this->isEnabled()) return;

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
    if(!this->isEnabled()) return;

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

void drawScale(QPainter &painter, int size, int imageSize, int offset, const QFont &font) {
    int scaledSize = imageSize * size;
    float step = RULE_STEP_PX_MIN;
    for (int d = 1; d <= 20; ++d) {
        float sf = (float)scaledSize / d;
        if (sf < RULE_STEP_PX_MIN) {
            break;
        }
        if (imageSize % d == 0) {
            step = sf;
        }
    }
    float pxStep = imageSize / ((float)scaledSize / step);
    float fromStartToZero = qCeil(offset / step);
    float px = -pxStep * fromStartToZero;

    for (int i = offset - step * fromStartToZero; i < size; i += step, px += pxStep) {
        QString label = QString::number(px, 'f', 0);
        painter.drawText(QPointF(i + 5, 18), label);
        painter.drawLine(i, 4, i, 22);
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

        /****************************************************************************************************************/
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

        /****************************************************************************************************************/
        // pixel grid (jen kdyz je obrazek hodne priblizen)
        int s_w = this->image->width * this->scale;
        int s_h = this->image->height * this->scale;
        if(this->scale >= PIXEL_GRID_MIN_SCALE) {
            painter.setPen(QColor(100, 100, 100));
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

        /****************************************************************************************************************/
        // vykresleni ramecku meritek
        painter.fillRect(26, 0, this->width(), 26, QBrush(QColor(50, 50, 50), Qt::SolidPattern));
        painter.fillRect(0, 26, 26, this->height(), QBrush(QColor(50, 50, 50), Qt::SolidPattern));
        painter.setFont(this->config.font);
        painter.setPen(QColor(150, 150, 150));


        // vekresleni meritek ose
        int ruleXStart = 0;
        while(ruleXStart > -offset.x() && this->scale != 0) {
            ruleXStart -= this->scale * 4;
        }
        int ruleYStart = 0;
        while(ruleYStart > -offset.y() && this->scale != 0) {
            ruleYStart -= this->scale * 4;
        }

        int ruleXEnd = this->width() - offset.x();
        int ruleYEnd = this->height() - offset.y();

        // x osa meritko
        float rulePos;
        float lastRulePoint;
        float px = 0;
        // vykresleni meritka v jednom smeru ->
        lastRulePoint = 999999;
        for(float x = 0; (int)x < ruleXEnd; x += this->scale * 2) {
            rulePos = offset.x() + x;
            if(std::abs(lastRulePoint - rulePos) >= RULE_STEP_PX_MIN) {
                lastRulePoint = rulePos;
                px = (x/s_w) * this->image->width;
                painter.drawText(QPointF(rulePos + 5, 18), QString::number(px, 'f', 0));
                painter.drawLine(rulePos, 4, rulePos, 22);
            }
        }
        // vykresleni meritka v jednom smeru <-
        lastRulePoint = 999999;
        for(float x = 0; (int)x > ruleXStart; x -= this->scale * 2) {
            rulePos = offset.x() + x;
            if(std::abs(lastRulePoint - rulePos) >= RULE_STEP_PX_MIN) {
                lastRulePoint = rulePos;
                px = (x/s_w) * this->image->width;
                painter.drawText(QPointF(rulePos + 5, 18), QString::number(px, 'f', 0));
                painter.drawLine(rulePos, 4, rulePos, 22);
            }
        }

        // y osa meritko
        QString buffer = "";
        QFontMetrics fm(this->config.font);
        // vykresleni meritka v jednom smeru ->
        lastRulePoint = 999999;
        for(float y = 0; (int)y < ruleYEnd; y += this->scale * 2) {
            rulePos = offset.y() + y;
            if(std::abs(lastRulePoint - rulePos) >= RULE_STEP_PX_MIN) {
                lastRulePoint = rulePos;
                px = (y/s_h) * this->image->height;

                buffer = QString::number(px, 'f', 0);
                uint16_t i = 0;
                for(QChar &c : buffer) {
                    painter.drawText(QPointF(8, rulePos + (i + 0.9) * (fm.height() - 4) + 5), c);
                    ++i;
                }
                painter.drawLine(4, rulePos, 22, rulePos);
            }
        }
        // vykresleni meritka v jednom smeru <-
        lastRulePoint = 999999;
        for(float y = 0; (int)y > ruleYStart; y -= this->scale * 2) {
            rulePos = offset.y() + y;
            if(std::abs(lastRulePoint - rulePos) >= RULE_STEP_PX_MIN) {
                lastRulePoint = rulePos;
                px = (y/s_h) * this->image->height;

                buffer = QString::number(px, 'f', 0);
                uint16_t i = 0;
                for(QChar &c : buffer) {
                    painter.drawText(QPointF(8, rulePos + (i + 0.9) * (fm.height() - 4) + 5), c);
                    ++i;
                }
                painter.drawLine(4, rulePos, 22, rulePos);
            }
        }

        // stredovy ramecek meritek
        painter.fillRect(0, 0, 26, 26, QBrush(QColor(46, 46, 46), Qt::SolidPattern));


        /****************************************************************************************************************/
        // pozicni informace
        painter.fillRect(26, this->height() - 26, this->width(), 26, QBrush(QColor(45, 45, 45), Qt::SolidPattern));
        painter.setPen(QColor(210, 150, 150));
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
        pos = pos - this->calculateEventOffsetPosition(this->lastPressPos, b);
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
    // nyni uz finalni pozice prepoctena na soradnice v obrazku
    offset *= INV_SCALE(this->scale);

    // pokud je mimo kreslici plochu tak zneplatni hodnoty
    if(offset.x() < 0 || offset.y() < 0 || offset.x() > this->image->width || offset.y() > this->image->height) {
        outOfRange = true;
    } else {
        outOfRange = false;
    }

    return offset;
}

