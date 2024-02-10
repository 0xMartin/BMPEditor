#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Image/bmpimage.h"
#include "Base/error.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**********************************************************/
    // toolbar
    this->ui->toolBar->addAction(this->ui->actionOpen);
    this->ui->toolBar->addAction(this->ui->actionSave);
    this->ui->toolBar->addWidget(this->createToolbarSeparator());
    this->ui->toolBar->addAction(this->ui->actionUndo);
    this->ui->toolBar->addAction(this->ui->actionRedo);
    this->ui->toolBar->addWidget(this->createToolbarSeparator());
    this->ui->toolBar->addAction(this->ui->actionZoom_in);
    this->ui->toolBar->addAction(this->ui->actionZoom_out);
    this->ui->toolBar->addAction(this->ui->actionReset_scale);
    this->ui->toolBar->addWidget(this->createToolbarSeparator());
    this->ui->toolBar->addAction(this->ui->actionRotate_90_plus);
    this->ui->toolBar->addAction(this->ui->actionRotate_90_minus);
    this->ui->toolBar->addAction(this->ui->actionFlip_horizontally);
    this->ui->toolBar->addAction(this->ui->action_Flip_vertically);

    /**********************************************************/
    // histori (undo, redo)
    this->ui->actionUndo->setEnabled(false);
    this->ui->actionRedo->setEnabled(false);

    /**********************************************************/
    // status bar
    QWidget *statusBarWidget = new QWidget(this->ui->statusbar);

    this->statusLabel = new QLabel(statusBarWidget);
    this->statusLabel->setAlignment(Qt::AlignLeft);
    this->statusLabel->setText(tr("<b>Status:</b> No image"));

    this->pathLabel = new QLabel(statusBarWidget);
    this->pathLabel->setAlignment(Qt::AlignLeft);
    this->pathLabel->setText(tr("<b>Path:</b> None"));

    QHBoxLayout * statusBarLayour = new QHBoxLayout(statusBarWidget);
    statusBarLayour->setContentsMargins(6, 2, 2, 2);
    statusBarWidget->setLayout(statusBarLayour);
    statusBarLayour->addWidget(this->statusLabel);
    statusBarLayour->addWidget(this->pathLabel);
    statusBarLayour->addStretch();

    this->statusBar()->addPermanentWidget(statusBarWidget, 1);

    /**********************************************************/
    // progress dialog
    progressDialog.cancel();
    progressDialog.setLabelText("Loading...");
    progressDialog.setCancelButton(nullptr); // Bez tlačítka pro zrušení
    progressDialog.setWindowFlags(progressDialog.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setRange(0, 0);

    /**********************************************************/
    // init
    this->image = NULL;

    /**********************************************************/
    // vytvoreni a konfigurace workspacu
    Config_Workspace_t cnfg;
    cnfg.font.setFamily("Monospace");
    cnfg.font.setPixelSize(11);
    cnfg.font.setStyle(QFont::StyleNormal);
    cnfg.fps = 50;
    cnfg.mouseSensitivity = 1.3;
    this->workspace = new Workspace(cnfg, this);

    /**********************************************************/
    // vytvoreni image info panelu
    this->imageInfoPanel = new ImageInfoPanel(this);

    /**********************************************************/
    // nastaveni image utils tridy
    connect(&this->imgUtils, &ImageUtils::imageChangedSignal, this, &MainWindow::imageChanged);
    connect(&this->imgUtils, &ImageUtils::jobStart, this, &MainWindow::imageUtilsJobStart);
    connect(&this->imgUtils, &ImageUtils::jobFinished, this, &MainWindow::imageUtilsJobFinished);

    /**********************************************************/
    // sestaveni celkove pracovni plochy s vyuzitim splitteru
    this->splitter_horizontal = new QSplitter(Qt::Horizontal);
    this->splitter_horizontal->setObjectName("bg-widget");
    // leva strana (info panel)
    this->splitter_horizontal->addWidget(this->imageInfoPanel);
    // prava strana (workspace)
    this->splitter_horizontal->addWidget(this->workspace);
    this->setCentralWidget(this->splitter_horizontal);
    this->splitter_horizontal->setStretchFactor(0, 1);
    this->splitter_horizontal->setStretchFactor(1, 2);
}

MainWindow::~MainWindow()
{
    progressDialog.hide();
    delete ui;
}

void MainWindow::setImage(Image *image)
{
    // pokud je aktualne otevren nejaky obrazek tak ho odstrani z pameti
    if(this->image != NULL) {
        delete this->image;
        this->image = NULL;
    }

    // nastaveni pointeru obrazku hlavnim prvkum editoru
    this->image = image;
    this->workspace->setImage(this->image);
    this->workspace->setDefaultScale();
    this->workspace->setDefaultOffset();
    this->imageInfoPanel->setImage(this->image);
    this->imgUtils.setCurrentImage(this->image);

    // status bar
    this->statusLabel->setText(tr("<b>Status:</b> Image loaded"));
    this->pathLabel->setText(tr("<b>Path:</b> ") + image->imgPath);
}

QFrame *MainWindow::createToolbarSeparator()
{
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    return separator;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // app: close event dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Close", "Are you sure you want to exit the application?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        progressDialog.hide();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::imageChanged(const QString &message)
{
    // obrazek byl zmenen nejaky zpusobem

    // repaint request
    this->workspace->repaint();
    this->imageInfoPanel->refresh();

    // status bar
    this->statusLabel->setText(tr("<b>Status:</b> ") + message);

    // zmena stavu tlacitek pro rizeni historie (undo, redo)
    this->ui->actionUndo->setEnabled(this->imgUtils.getHistoryIndex() > 0);
    this->ui->actionRedo->setEnabled(this->imgUtils.getHistoryIndex() + 1 < this->imgUtils.getImageHistory().size());
}

void MainWindow::imageUtilsJobStart()
{
    this->progressDialog.show();
    this->setEnabled(false);
}

void MainWindow::imageUtilsJobFinished()
{
    this->progressDialog.hide();
    this->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{
    // app: load image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("BMP File (*.bmp)"));
    if (!fileName.isEmpty()) {
        qDebug() << "Open file: " << fileName;
        BMPImage *bmp = new BMPImage();
        this->statusLabel->setText(tr("<b>Status:</b> Image loading ..."));
        int errCode = bmp->loadImage(fileName);
        if(errCode != STATUS_OK) {
            // nastala chyba pri nacteni souboru
            QString errorStr;
            getErrorCodeInfo(errCode, errorStr);
            QMessageBox::critical(this, tr("Open Error"), QString(tr("Failed to open BMP image. Error: %1")).arg(errorStr));
            this->statusLabel->setText(tr("<b>Status:</b> Failed to load image"));
        } else {
            // obrazek uspesne nacten => zobrazeni v editoru
            this->setImage(bmp);
            QMessageBox::information(this, "Open Image", "Image opened successfully!");
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    // app: save image
    if(this->image == NULL) {
        QMessageBox::critical(this, tr("Save Error"), tr("It is not possible to save an image because no image is opened!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::homePath(), tr("BMP file (*.bmp)"));
        if (!fileName.isEmpty()) {
            qDebug() << "Save file: " << fileName;
            this->statusLabel->setText(tr("<b>Status:</b> Image saving ..."));
            int errCode = this->image->saveImage(fileName);
            if(errCode != STATUS_OK) {
                // nastala chyba pri nacteni souboru
                QString errorStr;
                getErrorCodeInfo(errCode, errorStr);
                QMessageBox::critical(this, tr("Save Error"), QString(tr("Failed to save BMP image. Error: %1")).arg(errorStr));
                this->statusLabel->setText(tr("<b>Status:</b> Failed to save image"));
            } else {
                QMessageBox::information(this, "Save Image", "Image saved successfully!");
                this->statusLabel->setText(tr("<b>Status:</b> Image saved"));
            }
        }
    }
}


void MainWindow::on_actionAbout_triggered()
{
    // app: about section
    dialog.show();
}


void MainWindow::on_actionExit_triggered()
{
    // app: close
    QCloseEvent *event = new QCloseEvent();
    closeEvent(event);
    if(event->isAccepted()) {
        exit(0);
    }
    delete event;
}


void MainWindow::on_actionZoom_in_triggered()
{
    // workspace: zoom in
    if(this->image != NULL && this->workspace != NULL) {
        this->workspace->zoomIN();
        this->workspace->repaint();
    }
}


void MainWindow::on_actionZoom_out_triggered()
{
    // workspace: zoom out
    if(this->image != NULL && this->workspace != NULL) {
        this->workspace->zoomOUT();
        this->workspace->repaint();
    }
}


void MainWindow::on_actionReset_scale_triggered()
{
    // workspace: default scale & position
    if(this->image != NULL && this->workspace != NULL) {
        this->workspace->setDefaultOffset();
        this->workspace->setDefaultScale();
        this->workspace->repaint();
    }
}


void MainWindow::on_actionUndo_triggered()
{
    // undo
    if(this->image != NULL) {
        this->imgUtils.undo();
    }
}


void MainWindow::on_actionRedo_triggered()
{
    // redo
    if(this->image != NULL) {
        this->imgUtils.redo();
    }
}


void MainWindow::on_actionRotate_90_plus_triggered()
{
    // image traformation : rotate +90
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.rotateClockwise());
    }
}


void MainWindow::on_actionRotate_90_minus_triggered()
{
    // image traformation : rotate -90
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.rotateCounterClockwise());
    }
}

void MainWindow::on_actionFlip_horizontally_triggered()
{
    // image traformation : flip H
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.flipHorizontally());
    }
}

void MainWindow::on_action_Flip_vertically_triggered()
{
    // image traformation : flip V
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.flipVertically());
    }
}

void MainWindow::on_actionGrayscale_triggered()
{
    // image filter : grayscale
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.applyGrayscaleFilter());
    }
}

void MainWindow::on_actionInvert_triggered()
{
    // image filter : invert
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.applyInvertFilter());
    }
}

void MainWindow::on_actionSepia_triggered()
{
    // image filter : sepia
    if(this->image != NULL) {
        IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.applySepiaFilter());
    }
}

void MainWindow::on_actionBlur_triggered()
{
    // image filer: bluer
    if(this->image != NULL) {
        if (blurDialog.exec() == QDialog::Accepted) {
            int radius = blurDialog.getBlurRadius();
            IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.applyBlurFilter(radius));
        }
    }
}

void MainWindow::on_actionBrightness_triggered()
{
    // image filer: brightness
    if(this->image != NULL) {
        if (brightnessDialog.exec() == QDialog::Accepted) {
            int radius = blurDialog.getBlurRadius();
            IMG_UTIL_ASYNC(this->imgUtils, this->imgUtils.applyBrightnessAdjustment(radius));
        }
    }
}

void MainWindow::on_actionContrast_triggered()
{

}

