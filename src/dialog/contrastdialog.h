#ifndef CONTRASTDIALOG_H
#define CONTRASTDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class ContrastDialog : public QDialog {
    Q_OBJECT

public:
    explicit ContrastDialog(QWidget *parent = nullptr);

    void resetDialog();

    int getContrastValue() const;

private:
    QSlider *contrastSlider;
    QLabel *valueLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;

private slots:
    void updateValueLabel(int value);

};

#endif // CONTRASTDIALOG_H
