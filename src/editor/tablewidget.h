#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>

class CustomTableWidget : public QTableWidget {
    Q_OBJECT
public:
    explicit CustomTableWidget(QWidget *parent = nullptr);

    void addRow(const QString &fieldName, const QString &value);
};

#endif // TABLEWIDGET_H
