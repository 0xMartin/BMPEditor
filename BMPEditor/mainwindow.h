#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

#include "Base/image.h"
#include "Base/imageutils.h"
#include "Editor/workspace.h"
#include "Editor/imageinfopanel.h"
#include "about.h"

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

    void setImage(Image *image);

protected:
    // aktualni obrazek
    Image *image;

    // nastroj pro modifikace aktualniho obrazku
    ImageUtils imgUtils;

    // hlavni prvky editoru
    Workspace *workspace;
    ImageInfoPanel *imageInfoPanel;
    QLabel *statusLabel;

    // dialogy
    AboutDialog dialog;

    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionReset_scale_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionRotate_90_plus_triggered();

    void on_actionRotate_90_minus_triggered();

    void on_actionFlip_horizontally_triggered();

    void on_action_Flip_vertically_triggered();

private:
    Ui::MainWindow *ui;
    QSplitter * splitter_horizontal;

    QFrame *createToolbarSeparator();
};
#endif // MAINWINDOW_H
