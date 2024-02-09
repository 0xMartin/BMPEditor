#include "about.h"

#include <QPushButton>
#include <QDesktopServices>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/Resources/icon.png"), QSize(), QIcon::Normal, QIcon::On);
    this->setWindowIcon(icon);
    this->setWindowTitle("About");

    connect(ui.pushButtonGithub, &QPushButton::clicked, this, &AboutDialog::openGithub);
    connect(ui.pushButtonClose, &QPushButton::clicked, this, &AboutDialog::closeDialog);
}

AboutDialog::~AboutDialog() {}

void AboutDialog::openGithub() {
    QDesktopServices::openUrl(QUrl("https://github.com/0xMartin"));
}

void AboutDialog::closeDialog() {
    close();
}
