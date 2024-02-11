#include "tablewidget.h"

#include <QHeaderView>
#include <QIcon>

CustomTableWidget::CustomTableWidget(QWidget *parent) : QTableWidget(parent) {
    // vytvoreni tabulky
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setColumnCount(2);
    this->horizontalHeader()->setStretchLastSection(true);

    // vytvoreni nazvu sloupcu v tabulce
    QTableWidgetItem *headerItem1 = new QTableWidgetItem("Name");
    QFont font = headerItem1->font();
    font.setBold(true);
    headerItem1->setFont(font);
    headerItem1->setBackground(Qt::lightGray);
    headerItem1->setFlags(headerItem1->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *headerItem2 = new QTableWidgetItem("Value");
    font = headerItem2->font();
    font.setBold(true);
    headerItem2->setFont(font);
    headerItem2->setBackground(Qt::lightGray);
    headerItem2->setFlags(headerItem2->flags() & ~Qt::ItemIsEditable);

    this->setHorizontalHeaderItem(0, headerItem1);
    this->setHorizontalHeaderItem(1, headerItem2);

    this->setStyleSheet("QTableWidget { border: 0px solid rgb(20, 20, 20); }");
}

void CustomTableWidget::addRow(const QString &fieldName, const QString &value)
{
    int row = this->rowCount();
    this->insertRow(row);
    QLabel *item = new QLabel();
    item->setText(fieldName);
    this->setCellWidget(row, 0, item);
    item = new QLabel(value);
    item->setText(value);
    this->setCellWidget(row, 1, item);
}

