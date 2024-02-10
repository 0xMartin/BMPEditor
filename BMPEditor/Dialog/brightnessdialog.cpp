#include "brightnessdialog.h"

#include "brightnessdialog.h"

BrightnessDialog::BrightnessDialog(QWidget *parent) : QDialog(parent)
{
    // Vytvoření slideru pro nastavení jasu
    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setMinimum(-100);
    brightnessSlider->setMaximum(100);
    brightnessSlider->setValue(0);

    // Vytvoření popisku pro zobrazení hodnoty jasu
    valueLabel = new QLabel("0");

    // Vytvoření tlačítek pro OK a Storno
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    // Propojení signálů a slotů
    connect(okButton, &QPushButton::clicked, this, &BrightnessDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &BrightnessDialog::reject);
    connect(brightnessSlider, &QSlider::valueChanged, this, &BrightnessDialog::updateValueLabel);

    // Sestavení rozložení
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(brightnessSlider);
    layout->addWidget(valueLabel);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    // Nastavení titulku a minimální velikosti dialogu
    setWindowTitle("Brightness Adjustment");
    setMinimumSize(300, 100);
}

int BrightnessDialog::getBrightnessValue() const
{
    return brightnessSlider->value();
}

void BrightnessDialog::updateValueLabel(int value)
{
    valueLabel->setText(QString::number(value));
}
