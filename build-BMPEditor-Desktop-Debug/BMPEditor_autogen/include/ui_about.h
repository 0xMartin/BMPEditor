/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonGithub;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(448, 488);
        verticalLayout_2 = new QVBoxLayout(About);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(250, 250));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Resources/icon.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(About);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButtonGithub = new QPushButton(About);
        pushButtonGithub->setObjectName(QString::fromUtf8("pushButtonGithub"));
        QFont font;
        font.setPointSize(12);
        pushButtonGithub->setFont(font);

        verticalLayout->addWidget(pushButtonGithub);

        pushButtonClose = new QPushButton(About);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setFont(font);

        verticalLayout->addWidget(pushButtonClose);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("About", "<html><head/><body><h1 style=\" margin-top:18px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:xx-large; font-weight:700;\">BMP Editor</span></h1><p><span style=\" font-weight:700;\">Author:</span> Martin Kr\304\215ma<br/><span style=\" font-weight:700;\">Last Update:</span> 12. 2. 2024<br/><span style=\" font-weight:700;\">Version:</span> 0.2.1</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonGithub->setToolTip(QCoreApplication::translate("About", "https://github.com/0xMartin", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGithub->setText(QCoreApplication::translate("About", "Github", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("About", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
