/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionRotate_90_plus;
    QAction *actionRotate_90_minus;
    QAction *actionFlip_horizontally;
    QAction *action_Flip_vertically;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionReset_scale;
    QAction *actionWrite_message;
    QAction *actionClear_message;
    QAction *actionAbout;
    QAction *actionRead_message;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionExit;
    QAction *actionConvert_to_1b_BMP;
    QAction *actionConvert_to_4b_BMP;
    QAction *actionConvert_to_8b_BMP;
    QAction *actionConvert_to_24b_BMP;
    QAction *actionGrayscale;
    QAction *actionInvert;
    QAction *actionSepia;
    QAction *actionBlur;
    QAction *actionBrightness;
    QAction *actionContrast;
    QAction *actionColor_balance;
    QAction *actionSharpen;
    QAction *actionEdge_Detection;
    QAction *actionEmboss;
    QAction *actionApply_Custom_Kernel;
    QAction *actionImport_as_BMP_24;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuFilter;
    QMenu *menuTransform;
    QMenu *menuView;
    QMenu *menuSteganography;
    QMenu *menuHelp;
    QMenu *menuFormat;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1274, 806);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/icon.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindow->setWindowIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/file_open.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/file_save.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon2);
        actionRotate_90_plus = new QAction(MainWindow);
        actionRotate_90_plus->setObjectName("actionRotate_90_plus");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/rotate_plus.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionRotate_90_plus->setIcon(icon3);
        actionRotate_90_minus = new QAction(MainWindow);
        actionRotate_90_minus->setObjectName("actionRotate_90_minus");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/rotate_minus.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionRotate_90_minus->setIcon(icon4);
        actionFlip_horizontally = new QAction(MainWindow);
        actionFlip_horizontally->setObjectName("actionFlip_horizontally");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/flip_horizontal.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionFlip_horizontally->setIcon(icon5);
        action_Flip_vertically = new QAction(MainWindow);
        action_Flip_vertically->setObjectName("action_Flip_vertically");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/flip_vertical.svg"), QSize(), QIcon::Normal, QIcon::On);
        action_Flip_vertically->setIcon(icon6);
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName("actionZoom_in");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/zoom_in.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionZoom_in->setIcon(icon7);
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName("actionZoom_out");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/zoom_out.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionZoom_out->setIcon(icon8);
        actionReset_scale = new QAction(MainWindow);
        actionReset_scale->setObjectName("actionReset_scale");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/reset_scale.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset_scale->setIcon(icon9);
        actionWrite_message = new QAction(MainWindow);
        actionWrite_message->setObjectName("actionWrite_message");
        actionClear_message = new QAction(MainWindow);
        actionClear_message->setObjectName("actionClear_message");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionRead_message = new QAction(MainWindow);
        actionRead_message->setObjectName("actionRead_message");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/undo.svg"), QSize(), QIcon::Normal, QIcon::On);
        actionUndo->setIcon(icon10);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Resources/redo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon11);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionConvert_to_1b_BMP = new QAction(MainWindow);
        actionConvert_to_1b_BMP->setObjectName("actionConvert_to_1b_BMP");
        actionConvert_to_4b_BMP = new QAction(MainWindow);
        actionConvert_to_4b_BMP->setObjectName("actionConvert_to_4b_BMP");
        actionConvert_to_8b_BMP = new QAction(MainWindow);
        actionConvert_to_8b_BMP->setObjectName("actionConvert_to_8b_BMP");
        actionConvert_to_24b_BMP = new QAction(MainWindow);
        actionConvert_to_24b_BMP->setObjectName("actionConvert_to_24b_BMP");
        actionGrayscale = new QAction(MainWindow);
        actionGrayscale->setObjectName("actionGrayscale");
        actionInvert = new QAction(MainWindow);
        actionInvert->setObjectName("actionInvert");
        actionSepia = new QAction(MainWindow);
        actionSepia->setObjectName("actionSepia");
        actionBlur = new QAction(MainWindow);
        actionBlur->setObjectName("actionBlur");
        actionBrightness = new QAction(MainWindow);
        actionBrightness->setObjectName("actionBrightness");
        actionContrast = new QAction(MainWindow);
        actionContrast->setObjectName("actionContrast");
        actionColor_balance = new QAction(MainWindow);
        actionColor_balance->setObjectName("actionColor_balance");
        actionSharpen = new QAction(MainWindow);
        actionSharpen->setObjectName("actionSharpen");
        actionEdge_Detection = new QAction(MainWindow);
        actionEdge_Detection->setObjectName("actionEdge_Detection");
        actionEmboss = new QAction(MainWindow);
        actionEmboss->setObjectName("actionEmboss");
        actionApply_Custom_Kernel = new QAction(MainWindow);
        actionApply_Custom_Kernel->setObjectName("actionApply_Custom_Kernel");
        actionImport_as_BMP_24 = new QAction(MainWindow);
        actionImport_as_BMP_24->setObjectName("actionImport_as_BMP_24");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1274, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuFile->setTearOffEnabled(false);
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName("menuFilter");
        menuTransform = new QMenu(menubar);
        menuTransform->setObjectName("menuTransform");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuSteganography = new QMenu(menubar);
        menuSteganography->setObjectName("menuSteganography");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        menuFormat = new QMenu(menubar);
        menuFormat->setObjectName("menuFormat");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuTransform->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menubar->addAction(menuFormat->menuAction());
        menubar->addAction(menuSteganography->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionImport_as_BMP_24);
        menuFile->addAction(actionExit);
        menuFilter->addAction(actionGrayscale);
        menuFilter->addAction(actionInvert);
        menuFilter->addAction(actionSepia);
        menuFilter->addSeparator();
        menuFilter->addAction(actionBrightness);
        menuFilter->addAction(actionContrast);
        menuFilter->addAction(actionColor_balance);
        menuFilter->addSeparator();
        menuFilter->addAction(actionBlur);
        menuFilter->addAction(actionSharpen);
        menuFilter->addAction(actionEmboss);
        menuFilter->addAction(actionEdge_Detection);
        menuFilter->addAction(actionApply_Custom_Kernel);
        menuTransform->addAction(actionRotate_90_plus);
        menuTransform->addAction(actionRotate_90_minus);
        menuTransform->addAction(actionFlip_horizontally);
        menuTransform->addAction(action_Flip_vertically);
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        menuView->addAction(actionReset_scale);
        menuView->addAction(actionUndo);
        menuView->addAction(actionRedo);
        menuSteganography->addAction(actionWrite_message);
        menuSteganography->addAction(actionRead_message);
        menuSteganography->addAction(actionClear_message);
        menuHelp->addAction(actionAbout);
        menuFormat->addAction(actionConvert_to_1b_BMP);
        menuFormat->addAction(actionConvert_to_4b_BMP);
        menuFormat->addAction(actionConvert_to_8b_BMP);
        menuFormat->addAction(actionConvert_to_24b_BMP);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BMP Editor", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRotate_90_plus->setText(QCoreApplication::translate("MainWindow", "Rotate +90\302\260", nullptr));
#if QT_CONFIG(shortcut)
        actionRotate_90_plus->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRotate_90_minus->setText(QCoreApplication::translate("MainWindow", "Rotate -90\302\260", nullptr));
#if QT_CONFIG(shortcut)
        actionRotate_90_minus->setShortcut(QCoreApplication::translate("MainWindow", "Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFlip_horizontally->setText(QCoreApplication::translate("MainWindow", "Flip horizontally", nullptr));
        action_Flip_vertically->setText(QCoreApplication::translate("MainWindow", "\n"
"Flip vertically", nullptr));
        actionZoom_in->setText(QCoreApplication::translate("MainWindow", "Zoom in", nullptr));
        actionZoom_out->setText(QCoreApplication::translate("MainWindow", "Zoom out", nullptr));
        actionReset_scale->setText(QCoreApplication::translate("MainWindow", "Reset Scale", nullptr));
        actionWrite_message->setText(QCoreApplication::translate("MainWindow", "Write message", nullptr));
        actionClear_message->setText(QCoreApplication::translate("MainWindow", "Clear message", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionRead_message->setText(QCoreApplication::translate("MainWindow", "Read message", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionConvert_to_1b_BMP->setText(QCoreApplication::translate("MainWindow", "Convert to 1b BMP", nullptr));
        actionConvert_to_4b_BMP->setText(QCoreApplication::translate("MainWindow", "Convert to 4b BMP", nullptr));
        actionConvert_to_8b_BMP->setText(QCoreApplication::translate("MainWindow", "Convert to 8b BMP", nullptr));
        actionConvert_to_24b_BMP->setText(QCoreApplication::translate("MainWindow", "Convert to 24b BMP", nullptr));
        actionGrayscale->setText(QCoreApplication::translate("MainWindow", "Grayscale", nullptr));
        actionInvert->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        actionSepia->setText(QCoreApplication::translate("MainWindow", "Sepia", nullptr));
        actionBlur->setText(QCoreApplication::translate("MainWindow", "Blur", nullptr));
        actionBrightness->setText(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
        actionContrast->setText(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        actionColor_balance->setText(QCoreApplication::translate("MainWindow", "Color balance", nullptr));
        actionSharpen->setText(QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        actionEdge_Detection->setText(QCoreApplication::translate("MainWindow", "Edge Detection", nullptr));
        actionEmboss->setText(QCoreApplication::translate("MainWindow", "Emboss", nullptr));
        actionApply_Custom_Kernel->setText(QCoreApplication::translate("MainWindow", "Apply Custom Kernel", nullptr));
        actionImport_as_BMP_24->setText(QCoreApplication::translate("MainWindow", "Import as BMP 24", nullptr));
#if QT_CONFIG(shortcut)
        actionImport_as_BMP_24->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuFilter->setTitle(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        menuTransform->setTitle(QCoreApplication::translate("MainWindow", "Transform", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuSteganography->setTitle(QCoreApplication::translate("MainWindow", "Steganography", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuFormat->setTitle(QCoreApplication::translate("MainWindow", "Format", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
