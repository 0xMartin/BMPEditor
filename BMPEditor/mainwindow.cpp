#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Image/bmpimage.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    // label pro status bar
    this->statusLabel = new QLabel(this->ui->statusbar);
    this->statusLabel->setAlignment(Qt::AlignLeft);
    this->statusLabel->setText(tr("Status: No image"));
    this->statusBar()->addPermanentWidget(this->statusLabel, 1);

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


    BMPImage * fake = new BMPImage();
    fake->type = IMG_BMP;
    fake->width = 300;
    fake->height = 200;
    this->workspace->setImage(fake);
    this->imageInfoPanel->setImage(fake);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete statusLabel;
    delete splitter_horizontal;
}

QFrame *MainWindow::createToolbarSeparator()
{
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    return separator;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("BMP File (*.bmp)"));
    if (!fileName.isEmpty()) {
        qDebug() << "Open file: " << fileName;
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::homePath(), tr("BMP file (*.bmp)"));
    if (!fileName.isEmpty()) {
        qDebug() << "Save file: " << fileName;
    }
}

