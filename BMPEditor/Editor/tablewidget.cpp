#include "tablewidget.h"

#include <QHeaderView>
#include <QIcon>

CustomTableWidget::CustomTableWidget(QWidget *parent) : QWidget(parent) {
    // vytvoreni tabulky
    tableWidget = new QTableWidget();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

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

    tableWidget->setHorizontalHeaderItem(0, headerItem1);
    tableWidget->setHorizontalHeaderItem(1, headerItem2);

    // sestaveni hlavniho layoutu
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void CustomTableWidget::addRow(const QString &fieldName, const QString &value)
{
    int row = this->tableWidget->rowCount();
    this->tableWidget->insertRow(row);
    this->tableWidget->setItem(row, 0, new QTableWidgetItem(fieldName));
    this->tableWidget->setItem(row, 1, new QTableWidgetItem(value));
}


QTableWidget *CustomTableWidget::getTable() const
{
    return tableWidget;
}
