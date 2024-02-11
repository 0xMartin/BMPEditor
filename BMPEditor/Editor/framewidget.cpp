#include "framewidget.h"

#include <QHeaderView>
#include <QVBoxLayout>


FrameWidget::FrameWidget(const QString &name, QWidget *content, QWidget *parent) : QWidget(parent) {
    this->content = content;

    // label
    this->label = new QLabel(name);
    QFont font = label->font();
    font.setBold(true);
    font.setPointSize(12);
    this->label->setFont(font);

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

    // signaly tlacitek
    connect(minimizeButton, &ClickableLabel::clicked, this, &FrameWidget::minimize);
    connect(maximizeButton, &ClickableLabel::clicked, this, &FrameWidget::maximize);

    // sestaveni layoutu pro header (label + tlacitka)
    QWidget *tabHeader = new QWidget(this);
    tabHeader->setMaximumSize(QSize(9999, 40));
    tabHeader->setStyleSheet("background-color: rgb(39, 39, 41); padding: 3px");
    QHBoxLayout *layout = new QHBoxLayout(tabHeader);
    tabHeader->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(this->label);
    layout->addStretch();
    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);

    // sestaveni hlavniho layout
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(0);
    layoutMain->addWidget(tabHeader);
    layoutMain->addWidget(this->content);

    this->setLayout(layoutMain);
}

QLabel *FrameWidget::getLabel() const
{
    return label;
}

void FrameWidget::minimize() {
    if(this->content != NULL) {
        this->content->hide();
    }
}

void FrameWidget::maximize() {
    if(this->content != NULL) {
        this->content->show();
    }
}
