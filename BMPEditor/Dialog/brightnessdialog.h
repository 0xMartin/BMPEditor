#ifndef BRIGHTNESSDIALOG_H
#define BRIGHTNESSDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class BrightnessDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BrightnessDialog(QWidget *parent = nullptr);

    int getBrightnessValue() const;

private:
    QSlider *brightnessSlider;
    QLabel *valueLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;

private slots:
    void updateValueLabel(int value);
};

#endif // BRIGHTNESSDIALOG_H
