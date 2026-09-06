#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "./ui_about.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutDialog;
}
QT_END_NAMESPACE

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private slots:
    void openGithub();
    void closeDialog();

private:
    Ui::About ui;
};

#endif // ABOUT_H
