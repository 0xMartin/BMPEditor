#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ResizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ResizeDialog(QWidget *parent = nullptr);

    // nastavi aktualni rozmery obrazku (pri otevreni dialogu)
    void setCurrentSize(int width, int height);

    int getWidth() const;
    int getHeight() const;

private slots:
    void widthChanged(int value);
    void heightChanged(int value);

private:
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCheckBox *keepAspectRatioCheckBox;
    double aspectRatio;
    bool updating;
};

#endif // RESIZEDIALOG_H
