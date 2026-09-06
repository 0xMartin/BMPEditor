#include "loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Loading");
    setFixedSize(200, 100);

    // label
    QLabel *label = new QLabel("Loading...");
    label->setAlignment(Qt::AlignCenter);

    // progress bar
    progressBar = new QProgressBar;
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    // main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(progressBar);
    setLayout(layout);
}

void LoadingDialog::updateProgress(int value) {
    progressBar->setValue(value);
}
