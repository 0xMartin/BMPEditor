#include "colorbalancedialog.h"

ColorBalanceDialog::ColorBalanceDialog(QWidget *parent): QDialog(parent) {
    setWindowTitle(tr("Color Balance"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    this->redSlider = createSlider("Červený", -100, 100, mainLayout);
    this->greenSlider = createSlider("Zelený", -100, 100, mainLayout);
    this->blueSlider = createSlider("Modrý", -100, 100, mainLayout);

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Storno"));

    connect(okButton, &QPushButton::clicked, this, &ColorBalanceDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ColorBalanceDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);
}

int ColorBalanceDialog::getRedIntensity() const {
    return redSlider.first->value();
}

int ColorBalanceDialog::getGreenIntensity() const {
    return greenSlider.first->value();
}

int ColorBalanceDialog::getBlueIntensity() const {
    return blueSlider.first->value();
}

void ColorBalanceDialog::resetDialog()
{
    this->redSlider.first->setValue(0);
    this->greenSlider.first->setValue(0);
    this->blueSlider.first->setValue(0);
}

std::pair<QSlider*, QLabel*> ColorBalanceDialog::createSlider(const QString &labelText, int minValue,
                                                                int maxValue, QVBoxLayout *mainLayout) {
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(minValue, maxValue);

    QLabel *label = new QLabel(labelText + ": 0");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(slider);

    mainLayout->addLayout(layout);

    connect(slider, &QSlider::valueChanged, [=](int value){
        label->setText(labelText + ": " + QString::number(value));
    });

    return std::make_pair(slider, label);
}
