#ifndef BLUR_DIALOG_H
#define BLUR_DIALOG_H

#include <QDialog>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class BlurDialog : public QDialog {
    Q_OBJECT

public:
    explicit BlurDialog(QWidget *parent = nullptr);

    void resetDialog();

    int getBlurRadius() const;

private slots:
    void updateLabel(int value);

private:
    QSlider *radiusSlider;
    QLabel *radiusLabel;
};

#endif // BLUR_DIALOG_H
