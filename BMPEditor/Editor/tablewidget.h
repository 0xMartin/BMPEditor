#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>

class CustomTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomTableWidget(QWidget *parent = nullptr);

    QTableWidget *getTable() const;

    void addRow(const QString &fieldName, const QString &value);

private:
    QTableWidget *tableWidget;
};

#endif // TABLEWIDGET_H
