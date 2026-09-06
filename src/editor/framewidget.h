#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "clickablelabel.h"

class FrameWidget : public QWidget {
    Q_OBJECT
public:
    explicit FrameWidget(const QString &name, QWidget *content, QWidget *parent = nullptr);

    QLabel *getLabel() const;

public slots:
    void minimize();
    void maximize();

private:
    QWidget *content;

    QLabel *label;
    ClickableLabel *minimizeButton;
    ClickableLabel *maximizeButton;
};

#endif // FRAMEWIDGET_H
