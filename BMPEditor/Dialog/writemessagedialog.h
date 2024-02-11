#ifndef WRITEMESSAGEDIALOG_H
#define WRITEMESSAGEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class WriteMessageDialog : public QDialog {
    Q_OBJECT
public:
    explicit WriteMessageDialog(QWidget *parent = nullptr);

    void resetDialog();

    QString getMessage() const;

private:
    QLineEdit *messageLineEdit;
};

#endif // WRITEMESSAGEDIALOG_H
