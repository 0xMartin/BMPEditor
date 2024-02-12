#include "kernelinputdialog.h"

KernelInputDialog::KernelInputDialog(QWidget *parent) : QDialog(parent)
{
    layout = new QGridLayout(this);
    titleLabel = new QLabel("Enter kernel values:", this);
    layout->addWidget(titleLabel, 0, 0, 1, 2);

    // Create input fields for kernel values
    for (int i = 0; i < 3; ++i) {
        kernelInputs.push_back(std::vector<QLineEdit*>());
        for (int j = 0; j < 3; ++j) {
            QLineEdit *lineEdit = new QLineEdit(this);
            kernelInputs[i].push_back(lineEdit);
            layout->addWidget(lineEdit, i + 1, j);
        }
    }

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);
    layout->addWidget(okButton, 4, 0);
    layout->addWidget(cancelButton, 4, 1);

    connect(okButton, &QPushButton::clicked, this, &KernelInputDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &KernelInputDialog::onCancelClicked);
}

KernelInputDialog::~KernelInputDialog()
{
    // Clean up
    delete layout;
    delete titleLabel;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            delete kernelInputs[i][j];
        }
    }
    delete okButton;
    delete cancelButton;
}

void KernelInputDialog::onOkClicked()
{
    this->kernel.clear();
    for (int i = 0; i < 3; ++i) {
        this->kernel.push_back(std::vector<int>());
        for (int j = 0; j < 3; ++j) {
            this->kernel[i].push_back(kernelInputs[i][j]->text().toInt());
        }
    }
    emit kernelEntered(this->kernel);
    accept();
}

void KernelInputDialog::onCancelClicked()
{
    emit canceled();
    reject();
}

std::vector<std::vector<int> > KernelInputDialog::getKernel() const
{
    return kernel;
}
