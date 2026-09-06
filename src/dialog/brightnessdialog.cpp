#include "brightnessdialog.h"

#include "brightnessdialog.h"

BrightnessDialog::BrightnessDialog(QWidget *parent) : QDialog(parent)
{
    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setMinimum(-100);
    brightnessSlider->setMaximum(100);
    brightnessSlider->setValue(0);

    valueLabel = new QLabel("0");

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    connect(okButton, &QPushButton::clicked, this, &BrightnessDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &BrightnessDialog::reject);
    connect(brightnessSlider, &QSlider::valueChanged, this, &BrightnessDialog::updateValueLabel);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(brightnessSlider);
    layout->addWidget(valueLabel);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    setWindowTitle("Brightness Adjustment");
    setMinimumSize(300, 100);
}

void BrightnessDialog::resetDialog()
{
    this->brightnessSlider->setValue(0);
}

int BrightnessDialog::getBrightnessValue() const
{
    return brightnessSlider->value();
}

void BrightnessDialog::updateValueLabel(int value)
{
    valueLabel->setText(QString::number(value));
}
