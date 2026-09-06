#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

class LoadingDialog : public QDialog {
public:
    LoadingDialog(QWidget *parent = nullptr);

    void updateProgress(int value);

private:
    QProgressBar *progressBar;
};

#endif // LOADINGDIALOG_H
