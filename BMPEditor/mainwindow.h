#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QProgressDialog>

#include "Base/image.h"
#include "Base/imageutils.h"
#include "Editor/workspace.h"
#include "Editor/imageinfopanel.h"
#include "about.h"
#include "Dialog/blurdialog.h"
#include "Dialog/brightnessdialog.h"
#include "Dialog/contrastdialog.h"
#include "Dialog/colorbalancedialog.h"
#include "Dialog/writemessagedialog.h"

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
    QLabel *pathLabel;

    // pro asynchronni spousteni
    ThreadRunner worker;

    // dialogy
    AboutDialog dialog;
    QProgressDialog progressDialog;
    BlurDialog blurDialog;
    BrightnessDialog brightnessDialog;
    ContrastDialog contrastDialog;
    ColorBalanceDialog colorBalanceDialog;
    WriteMessageDialog writeMessageDialog;

    void closeEvent(QCloseEvent *event);

    void formatBMP(int bitCount);

    void appActionActivation();

private slots:
    void imageChanged(const QString &message);
    void asyncJobStart();
    void asyncJobFinished();
    void formatDone(Image *img);

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

    void on_actionGrayscale_triggered();

    void on_actionInvert_triggered();

    void on_actionSepia_triggered();

    void on_actionBlur_triggered();

    void on_actionBrightness_triggered();

    void on_actionContrast_triggered();

    void on_actionColor_balance_triggered();

    void on_actionConvert_to_1b_BMP_triggered();

    void on_actionConvert_to_4b_BMP_triggered();

    void on_actionConvert_to_8b_BMP_triggered();

    void on_actionConvert_to_24b_BMP_triggered();

    void on_actionWrite_message_triggered();

    void on_actionRead_message_triggered();

    void on_actionClear_message_triggered();

private:
    Ui::MainWindow *ui;
    QSplitter * splitter_horizontal;

    QFrame *createToolbarSeparator();
};
#endif // MAINWINDOW_H
