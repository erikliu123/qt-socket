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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_p2p
{
public:
    QTextEdit *lineEdit_name;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *textEdit;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_send;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_send_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_send_2;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *p2p)
    {
        if (p2p->objectName().isEmpty())
            p2p->setObjectName(QStringLiteral("p2p"));
        p2p->resize(615, 602);
        p2p->setMinimumSize(QSize(500, 300));
        p2p->setMaximumSize(QSize(663, 622));
        p2p->setStyleSheet(QLatin1String("QFrame {\n"
"   \n"
"    background-position: top right;\n"
"    background-origin: content;\n"
"    background-repeat: none;\n"
"}\n"
"QLabel{\n"
"color:white;\n"
"\n"
"}"));
        lineEdit_name = new QTextEdit(p2p);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(90, 10, 111, 31));
        scrollArea = new QScrollArea(p2p);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(90, 40, 471, 401));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 469, 399));
        textEdit = new QTextEdit(scrollAreaWidgetContents);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 471, 401));
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
        layoutWidget = new QWidget(p2p);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 450, 381, 121));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_send = new QPushButton(layoutWidget);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_send->sizePolicy().hasHeightForWidth());
        pushButton_send->setSizePolicy(sizePolicy2);
        pushButton_send->setMinimumSize(QSize(50, 20));
        pushButton_send->setMaximumSize(QSize(200, 50));
        pushButton_send->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_send);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_send_3 = new QPushButton(layoutWidget);
        pushButton_send_3->setObjectName(QStringLiteral("pushButton_send_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_send_3->sizePolicy().hasHeightForWidth());
        pushButton_send_3->setSizePolicy(sizePolicy3);
        pushButton_send_3->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_send_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_send_2 = new QPushButton(layoutWidget);
        pushButton_send_2->setObjectName(QStringLiteral("pushButton_send_2"));
        sizePolicy3.setHeightForWidth(pushButton_send_2->sizePolicy().hasHeightForWidth());
        pushButton_send_2->setSizePolicy(sizePolicy3);
        pushButton_send_2->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px outset purple;\n"
"    background: gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_send_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        textEdit_2 = new QTextEdit(layoutWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout->addWidget(textEdit_2, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 3);
        gridLayout->setRowStretch(1, 1);

        retranslateUi(p2p);

        QMetaObject::connectSlotsByName(p2p);
    } // setupUi

    void retranslateUi(QWidget *p2p)
    {
        p2p->setWindowTitle(QApplication::translate("p2p", "Dialog", Q_NULLPTR));
        lineEdit_name->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("p2p", "\345\217\221\351\200\201", Q_NULLPTR));
        pushButton_send_3->setText(QApplication::translate("p2p", "\345\257\274\345\205\245\346\234\254\345\234\260\346\266\210\346\201\257", Q_NULLPTR));
        pushButton_send_2->setText(QApplication::translate("p2p", "\345\257\274\345\207\272\346\226\207\344\273\266", Q_NULLPTR));
        textEdit_2->setHtml(QApplication::translate("p2p", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
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
