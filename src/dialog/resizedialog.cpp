#include "resizedialog.h"

ResizeDialog::ResizeDialog(QWidget *parent) : QDialog(parent)
{
    this->aspectRatio = 1.0;
    this->updating = false;

    widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(1, 30000);
    heightSpinBox = new QSpinBox();
    heightSpinBox->setRange(1, 30000);

    keepAspectRatioCheckBox = new QCheckBox(tr("Keep aspect ratio"));
    keepAspectRatioCheckBox->setChecked(true);

    connect(widthSpinBox, &QSpinBox::valueChanged, this, &ResizeDialog::widthChanged);
    connect(heightSpinBox, &QSpinBox::valueChanged, this, &ResizeDialog::heightChanged);

    QHBoxLayout *widthLayout = new QHBoxLayout;
    widthLayout->addWidget(new QLabel(tr("Width:")));
    widthLayout->addWidget(widthSpinBox);

    QHBoxLayout *heightLayout = new QHBoxLayout;
    heightLayout->addWidget(new QLabel(tr("Height:")));
    heightLayout->addWidget(heightSpinBox);

    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    connect(okButton, &QPushButton::clicked, this, &ResizeDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ResizeDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(heightLayout);
    mainLayout->addWidget(keepAspectRatioCheckBox);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(tr("Resize Image"));
}

void ResizeDialog::setCurrentSize(int width, int height)
{
    this->updating = true;
    this->aspectRatio = height != 0 ? (double)width / height : 1.0;
    this->widthSpinBox->setValue(width);
    this->heightSpinBox->setValue(height);
    this->updating = false;
}

int ResizeDialog::getWidth() const
{
    return widthSpinBox->value();
}

int ResizeDialog::getHeight() const
{
    return heightSpinBox->value();
}

void ResizeDialog::widthChanged(int value)
{
    if(this->updating || !this->keepAspectRatioCheckBox->isChecked()) return;
    this->updating = true;
    this->heightSpinBox->setValue(qMax(1, (int)(value / this->aspectRatio)));
    this->updating = false;
}

void ResizeDialog::heightChanged(int value)
{
    if(this->updating || !this->keepAspectRatioCheckBox->isChecked()) return;
    this->updating = true;
    this->widthSpinBox->setValue(qMax(1, (int)(value * this->aspectRatio)));
    this->updating = false;
}
