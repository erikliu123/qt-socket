/********************************************************************************
** Form generated from reading UI file 'chatroom.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_H
#define UI_CHATROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *refreshAction;
    QAction *myinfoAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QLabel *myname_label;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;
    QMenu *infoMenu;
    QMenu *aboutMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(798, 638);
        MainWindow->setMinimumSize(QSize(775, 617));
        MainWindow->setMaximumSize(QSize(975, 686));
        refreshAction = new QAction(MainWindow);
        refreshAction->setObjectName(QStringLiteral("refreshAction"));
        refreshAction->setCheckable(true);
        myinfoAction = new QAction(MainWindow);
        myinfoAction->setObjectName(QStringLiteral("myinfoAction"));
        myinfoAction->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        myname_label = new QLabel(centralwidget);
        myname_label->setObjectName(QStringLiteral("myname_label"));

        gridLayout_2->addWidget(myname_label, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget::item\n"
"{\n"
"height:40px; /*\346\257\217\344\270\252item\347\232\204\351\253\230\345\272\246*/\n"
"font-size:20px; /*\345\255\227\344\275\223\345\244\247\345\260\217*/\n"
"}\n"
"\n"
"QListWidget::item::hover\n"
"{\n"
"background-color:rgb(9,150,200,100); /*\344\274\252\347\212\266\346\200\201\357\274\214\351\274\240\346\240\207\347\273\217\350\277\207\350\203\214\346\231\257\350\211\262*/\n"
"}\n"
"\n"
"QListWidget::item:selected\n"
"{\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc); /*\351\200\211\344\270\255\350\203\214\346\231\257\350\211\262*/\n"
"}"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 643, 551));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 6);

        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 798, 23));
        infoMenu = new QMenu(menubar);
        infoMenu->setObjectName(QStringLiteral("infoMenu"));
        aboutMenu = new QMenu(menubar);
        aboutMenu->setObjectName(QStringLiteral("aboutMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(infoMenu->menuAction());
        menubar->addAction(aboutMenu->menuAction());
        infoMenu->addAction(refreshAction);
        infoMenu->addAction(myinfoAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        refreshAction->setText(QApplication::translate("MainWindow", "refresh online user", Q_NULLPTR));
        refreshAction->setShortcut(QApplication::translate("MainWindow", "F5", Q_NULLPTR));
        myinfoAction->setText(QApplication::translate("MainWindow", "My info", Q_NULLPTR));
        myname_label->setText(QString());
        infoMenu->setTitle(QApplication::translate("MainWindow", "\344\277\241\346\201\257", Q_NULLPTR));
        aboutMenu->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_H
