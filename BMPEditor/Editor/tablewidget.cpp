#include "tablewidget.h"

#include <QHeaderView>
#include <QIcon>

CustomTableWidget::CustomTableWidget(const QString &name, QWidget *parent) : QWidget(parent) {
    // label tabulky
    this->label = new QLabel(name);
    QFont font = label->font();
    font.setBold(true);
    font.setPointSize(12);
    this->label->setFont(font);

    // vytvoreni tabulky
    tableWidget = new QTableWidget();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    // vytvoreni nazvu sloupcu v tabulce
    QTableWidgetItem *headerItem1 = new QTableWidgetItem("Name");
    font = headerItem1->font();
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

    // vytvoreni tlacitka (minimalizace)
    minimizeButton = new ClickableLabel(this);
    minimizeButton->setPixmap(QPixmap(":/Resources/minimize.svg").scaled(QSize(12, 12)));
    minimizeButton->setTextFormat(Qt::RichText);
    minimizeButton->setCursor(Qt::PointingHandCursor);
    minimizeButton->setToolTip(tr("Minimize"));
    minimizeButton->setOpenExternalLinks(true);

    // vytvoreni tlacitka (maximalizace)
    maximizeButton = new ClickableLabel(this);
    maximizeButton->setPixmap(QPixmap(":/Resources/maximize.svg").scaled(QSize(12, 12)));
    maximizeButton->setTextFormat(Qt::RichText);
    maximizeButton->setCursor(Qt::PointingHandCursor);
    maximizeButton->setToolTip(tr("Maximize"));
    maximizeButton->setOpenExternalLinks(true);

    // sestaveni layoutu headeru tabulky (label + tlacitka)
    QWidget *tabHeader = new QWidget(this);
    tabHeader->setStyleSheet("background-color: rgb(39, 39, 41); padding: 3px");
    QHBoxLayout *layout2 = new QHBoxLayout(tabHeader);
    layout2->addWidget(label);
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout2->addSpacerItem(spacer);
    layout2->addWidget(minimizeButton);
    layout2->addWidget(maximizeButton);

    // sestaveni hlavniho layoutu
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(tabHeader);
    layout->addWidget(tableWidget);
    setLayout(layout);

    // signaly tlacitek
    connect(minimizeButton, &ClickableLabel::clicked, this, &CustomTableWidget::minimize);
    connect(maximizeButton, &ClickableLabel::clicked, this, &CustomTableWidget::maximize);
}

void CustomTableWidget::minimize() {
    tableWidget->hide();
}

void CustomTableWidget::maximize() {
    tableWidget->show();
}

QLabel *CustomTableWidget::getLabel() const
{
    return label;
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
