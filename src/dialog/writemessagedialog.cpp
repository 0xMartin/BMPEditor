#include "writemessagedialog.h"

WriteMessageDialog::WriteMessageDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Write Message");

    QLabel *label = new QLabel("Enter your message:", this);

    this->messageLineEdit = new QLineEdit(this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &WriteMessageDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &WriteMessageDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(this->messageLineEdit);
    layout->addWidget(buttonBox);

    this->setLayout(layout);
}

void WriteMessageDialog::resetDialog()
{
    this->messageLineEdit->clear();
}

QString WriteMessageDialog::getMessage() const {
    return messageLineEdit->text();
}
