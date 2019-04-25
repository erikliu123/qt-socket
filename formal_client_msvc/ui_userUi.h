/********************************************************************************
** Form generated from reading UI file 'userUi.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERUI_H
#define UI_USERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QPushButton *refreshBtn;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *openFileBtn;
    QLineEdit *filepath;
    QPushButton *pushButton_4;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QStringLiteral("UserInterface"));
        UserInterface->resize(605, 555);
        centralwidget = new QWidget(UserInterface);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QPushButton#hover\n"
"{\n"
"background-color: rgb(0,130,150); //\344\274\252\347\212\266\346\200\201\347\273\217\350\277\207\346\227\266\350\203\214\346\231\257\350\211\262\n"
"border:2px solid #5F92B2; //\350\276\271\347\225\214\345\222\214\350\276\271\347\225\214\351\242\234\350\211\262\n"
"border-radius:5px; //\350\276\271\347\225\214\345\234\206\346\273\221\n"
"color:white; //\345\255\227\344\275\223\344\270\272\347\231\275\350\211\262\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 10, 81, 16));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(50, 30, 211, 221));
        listWidget = new QListWidget(centralwidget);
        QBrush brush(QColor(0, 170, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setBackground(brush1);
        __qlistwidgetitem->setForeground(brush);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(330, 30, 231, 381));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 330, 191, 31));
        refreshBtn = new QPushButton(centralwidget);
        refreshBtn->setObjectName(QStringLiteral("refreshBtn"));
        refreshBtn->setGeometry(QRect(330, 430, 113, 32));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(240, 330, 71, 32));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 300, 111, 21));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(140, 300, 101, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 260, 121, 28));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(100, 380, 111, 31));
        openFileBtn = new QPushButton(centralwidget);
        openFileBtn->setObjectName(QStringLiteral("openFileBtn"));
        openFileBtn->setGeometry(QRect(160, 440, 113, 32));
        filepath = new QLineEdit(centralwidget);
        filepath->setObjectName(QStringLiteral("filepath"));
        filepath->setGeometry(QRect(50, 410, 221, 31));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(50, 440, 113, 32));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 10, 72, 15));
        UserInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserInterface);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 605, 23));
        UserInterface->setMenuBar(menubar);
        statusbar = new QStatusBar(UserInterface);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        UserInterface->setStatusBar(statusbar);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QMainWindow *UserInterface)
    {
        UserInterface->setWindowTitle(QApplication::translate("UserInterface", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("UserInterface", "\347\246\273\347\272\277\346\266\210\346\201\257\357\274\232", Q_NULLPTR));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        listWidget->setSortingEnabled(__sortingEnabled);

        refreshBtn->setText(QApplication::translate("UserInterface", "\345\210\267\346\226\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("UserInterface", "\345\217\221\346\266\210\346\201\257", Q_NULLPTR));
        label_3->setText(QApplication::translate("UserInterface", "\346\216\245\346\224\266\350\200\205", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("UserInterface", "\346\237\245\347\234\213\347\246\273\347\272\277\346\266\210\346\201\257", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("UserInterface", "\345\273\272\347\253\213\346\226\207\344\273\266\350\277\236\346\216\245", Q_NULLPTR));
        openFileBtn->setText(QApplication::translate("UserInterface", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("UserInterface", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserInterface", "\345\234\250\347\272\277\347\224\250\346\210\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERUI_H
