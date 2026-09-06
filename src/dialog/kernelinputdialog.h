#ifndef KERNELINPUTDIALOG_H
#define KERNELINPUTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class KernelInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KernelInputDialog(QWidget *parent = nullptr);
    ~KernelInputDialog();

    std::vector<std::vector<int>> getKernel() const;

signals:
    void kernelEntered(const std::vector<std::vector<int>>& kernel);
    void canceled();

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    std::vector<std::vector<int>> kernel;

    QGridLayout *layout;
    QLabel *titleLabel;
    std::vector<std::vector<QLineEdit*>> kernelInputs;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // KERNELINPUTDIALOG_H
