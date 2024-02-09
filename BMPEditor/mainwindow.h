#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

#include "Base/image.h"
#include "Editor/workspace.h"
#include "Editor/imageinfopanel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // aktualni obrazek
    Image *image;

    // hlavni prvky editoru
    Workspace *workspace;
    ImageInfoPanel *imageInfoPanel;
    QLabel *statusLabel;

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QSplitter * splitter_horizontal;

    QFrame *createToolbarSeparator();
};
#endif // MAINWINDOW_H