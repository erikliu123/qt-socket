/********************************************************************************
** Form generated from reading UI file 'p2p.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_P2P_H
#define UI_P2P_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_p2p
{
public:
    QLabel *label;
    QPushButton *pushButton_send;
    QTextEdit *lineEdit_name;
    QTextEdit *textEdit_2;
    QPushButton *pushButton_send_2;
    QPushButton *pushButton_send_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *textEdit;

    void setupUi(QDialog *p2p)
    {
        if (p2p->objectName().isEmpty())
            p2p->setObjectName(QStringLiteral("p2p"));
        p2p->resize(580, 598);
        p2p->setMinimumSize(QSize(500, 300));
        p2p->setStyleSheet(QLatin1String("QFrame {\n"
"       foreground-color: purple;\n"
"   \n"
"    background-position: top right;\n"
"    background-origin: content;\n"
"    background-repeat: none;\n"
"}\n"
""));
        label = new QLabel(p2p);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 400, 91, 20));
        pushButton_send = new QPushButton(p2p);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(350, 480, 113, 32));
        pushButton_send->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));
        lineEdit_name = new QTextEdit(p2p);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(230, 400, 111, 31));
        textEdit_2 = new QTextEdit(p2p);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(60, 440, 281, 71));
        pushButton_send_2 = new QPushButton(p2p);
        pushButton_send_2->setObjectName(QStringLiteral("pushButton_send_2"));
        pushButton_send_2->setGeometry(QRect(370, 520, 81, 32));
        pushButton_send_2->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));
        pushButton_send_3 = new QPushButton(p2p);
        pushButton_send_3->setObjectName(QStringLiteral("pushButton_send_3"));
        pushButton_send_3->setGeometry(QRect(250, 520, 91, 32));
        pushButton_send_3->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));
        scrollArea = new QScrollArea(p2p);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(70, 10, 451, 371));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 449, 369));
        textEdit = new QTextEdit(scrollAreaWidgetContents);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 451, 371));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setStyleSheet(QLatin1String("QFrame {\n"
"       background-color: #FFE7BA;\n"
"    background-image: url(./img/qt.png);\n"
"    background-position: top right;\n"
"    background-origin: content;\n"
"    background-repeat: none;\n"
"}\n"
""));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        textEdit->setTabChangesFocus(true);
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(p2p);

        QMetaObject::connectSlotsByName(p2p);
    } // setupUi

    void retranslateUi(QDialog *p2p)
    {
        p2p->setWindowTitle(QApplication::translate("p2p", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("p2p", "\346\216\245\346\224\266\344\272\272\345\220\215\345\255\227", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("p2p", "\345\217\221\351\200\201", Q_NULLPTR));
        lineEdit_name->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        textEdit_2->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_send_2->setText(QApplication::translate("p2p", "\345\257\274\345\207\272\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_send_3->setText(QApplication::translate("p2p", "\345\257\274\345\205\245\346\234\254\345\234\260\346\266\210\346\201\257", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class p2p: public Ui_p2p {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_P2P_H
