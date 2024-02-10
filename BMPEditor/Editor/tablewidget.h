#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "clickablelabel.h"

class CustomTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomTableWidget(const QString &name, QWidget *parent = nullptr);

    QTableWidget *getTable() const;

    void addRow(const QString &fieldName, const QString &value);

    QLabel *getLabel() const;

signals:

public slots:
    void minimize();

    void maximize();

private:
    QLabel *label;
    QTableWidget *tableWidget;
    ClickableLabel *minimizeButton;
    ClickableLabel *maximizeButton;
};

#endif // TABLEWIDGET_H
