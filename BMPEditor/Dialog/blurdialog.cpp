#include "blurdialog.h"

BlurDialog::BlurDialog(QWidget *parent) : QDialog(parent) {
    // slider pro nastavovani blur
    radiusSlider = new QSlider(Qt::Horizontal);
    radiusSlider->setMinimum(1);
    radiusSlider->setMaximum(20);
    radiusSlider->setValue(1);
    connect(radiusSlider, &QSlider::valueChanged, this, &BlurDialog::updateLabel);

    // label pro zobrazovani aktualne nastaveneho radiusu
    radiusLabel = new QLabel("Blur radius: 1");

    // layout pro slider a label
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(radiusLabel);
    layout->addWidget(radiusSlider);

    // tlacitko pro potvrzeni
    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, this, &BlurDialog::accept);

    // layout pro usporadani tlacitka
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle("Blur Filter");
}

void BlurDialog::resetDialog()
{
    this->radiusSlider->setValue(0);
}

int BlurDialog::getBlurRadius() const {
    return radiusSlider->value();
}

void BlurDialog::updateLabel(int value) {
    radiusLabel->setText(QString("Blur radius: %1").arg(value));
}
