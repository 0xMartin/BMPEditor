#ifndef COLORBALANCEDIALOG_H
#define COLORBALANCEDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ColorBalanceDialog : public QDialog {
    Q_OBJECT
public:
    explicit ColorBalanceDialog(QWidget *parent = nullptr);

    int getRedIntensity() const;
    int getGreenIntensity() const;
    int getBlueIntensity() const;

    void resetDialog();

private:
    std::pair<QSlider*, QLabel*> createSlider(const QString &labelText,
                                                int minValue,
                                                int maxValue,
                                                QVBoxLayout *mainLayout);

    std::pair<QSlider*, QLabel*> redSlider;
    std::pair<QSlider*, QLabel*> greenSlider;
    std::pair<QSlider*, QLabel*> blueSlider;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // COLORBALANCEDIALOG_H
