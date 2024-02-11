#include "contrastdialog.h"

ContrastDialog::ContrastDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Contrast Adjustment"));

    contrastSlider = new QSlider(Qt::Horizontal);
    contrastSlider->setRange(-100, 100);
    contrastSlider->setValue(0);

    valueLabel = new QLabel("0");

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancle"));

    connect(okButton, &QPushButton::clicked, this, &ContrastDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ContrastDialog::reject);
    connect(contrastSlider, &QSlider::valueChanged, this, &ContrastDialog::updateValueLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(contrastSlider);
    mainLayout->addWidget(valueLabel);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);
}

void ContrastDialog::resetDialog()
{
    this->contrastSlider->setValue(0);
}

int ContrastDialog::getContrastValue() const {
    return contrastSlider->value();
}

void ContrastDialog::updateValueLabel(int value)
{
    valueLabel->setText(QString::number(value));
}
