/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *signBtn;
    QPushButton *sendBtn;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *passwardLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLineEdit *userLineEdit;
    QPushButton *resetpwdButton;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *ServerIp;
    QPushButton *link;
    QPushButton *dislink;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QStringLiteral("TcpClient"));
        TcpClient->resize(523, 370);
        TcpClient->setMinimumSize(QSize(523, 370));
        TcpClient->setMaximumSize(QSize(578, 370));
        TcpClient->setContextMenuPolicy(Qt::DefaultContextMenu);
        TcpClient->setStyleSheet(QLatin1String(" QPushButton {\n"
"           color: blue;\n"
"          /* border-image: url(D:/BaiduNetdiskDownload/build-Self_Defined_Window-Desktop_Qt_5_8_0_MinGW_32bit-Release/img/button2.jpg);*/\n"
" 			font:  14px;\n"
"           \n"
"        }\n"
"\n"
"QPushButton#evilButton {\n"
" border-image: url(:/image/img/button4.jpg);\n"
"    background-color: red;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: beige;\n"
"    font: bold 14px;\n"
"    min-width: 10em;\n"
"    padding: 6px;\n"
"}\n"
"/*QFrame, QLabel, Q*/\n"
"QMainWindow {\n"
"\n"
"    background-image: url(:/image/img/1.png);\n"
"}\n"
"QPushButton:pressed {\n"
"border-image: url(:/image/img/1.png);\n"
"    border-style: inset;\n"
"}\n"
"QLabel{\n"
"color:white;\n"
"\n"
"}\n"
"\n"
""));
        TcpClient->setAnimated(true);
        TcpClient->setDockNestingEnabled(false);
        centralWidget = new QWidget(TcpClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(50, 50, 50, 50);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(200, 0, 120, 50);
        signBtn = new QPushButton(centralWidget);
        signBtn->setObjectName(QStringLiteral("signBtn"));
        signBtn->setMinimumSize(QSize(50, 23));

        horizontalLayout->addWidget(signBtn);

        sendBtn = new QPushButton(centralWidget);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setMinimumSize(QSize(50, 23));

        horizontalLayout->addWidget(sendBtn);


        gridLayout_4->addLayout(horizontalLayout, 3, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(241, 25));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Devanagari"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_6->setFont(font);
        label_6->setCursor(QCursor(Qt::CrossCursor));
        label_6->setMouseTracking(false);
        label_6->setFocusPolicy(Qt::NoFocus);
        label_6->setStyleSheet(QLatin1String("QLabel{\n"
"color:white;\n"
"}"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_6->setContentsMargins(-1, -1, 110, -1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(39, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("Adobe Devanagari"));
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setStyleSheet(QLatin1String("QLabel{\n"
"color:white;\n"
"\n"
"}"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_2);

        passwardLineEdit = new QLineEdit(centralWidget);
        passwardLineEdit->setObjectName(QStringLiteral("passwardLineEdit"));
        sizePolicy1.setHeightForWidth(passwardLineEdit->sizePolicy().hasHeightForWidth());
        passwardLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(passwardLineEdit);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        gridLayout_4->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_5->setContentsMargins(-1, -1, 0, -1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(39, 23));
        label->setFont(font1);
        label->setStyleSheet(QLatin1String("QLabel{\n"
"color:white;\n"
"\n"
"}"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label);

        userLineEdit = new QLineEdit(centralWidget);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));
        sizePolicy1.setHeightForWidth(userLineEdit->sizePolicy().hasHeightForWidth());
        userLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(userLineEdit);

        resetpwdButton = new QPushButton(centralWidget);
        resetpwdButton->setObjectName(QStringLiteral("resetpwdButton"));
        sizePolicy1.setHeightForWidth(resetpwdButton->sizePolicy().hasHeightForWidth());
        resetpwdButton->setSizePolicy(sizePolicy1);
        resetpwdButton->setMinimumSize(QSize(78, 23));

        horizontalLayout_5->addWidget(resetpwdButton);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);
        horizontalLayout_5->setStretch(2, 1);

        gridLayout_4->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setStyleSheet(QLatin1String("QLabel{\n"
"color:black;\n"
"background-color:#ffffff;\n"
"}"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3, 0, Qt::AlignRight);

        ServerIp = new QLineEdit(centralWidget);
        ServerIp->setObjectName(QStringLiteral("ServerIp"));

        horizontalLayout_2->addWidget(ServerIp);

        link = new QPushButton(centralWidget);
        link->setObjectName(QStringLiteral("link"));
        link->setMinimumSize(QSize(75, 23));

        horizontalLayout_2->addWidget(link);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        dislink = new QPushButton(centralWidget);
        dislink->setObjectName(QStringLiteral("dislink"));
        sizePolicy.setHeightForWidth(dislink->sizePolicy().hasHeightForWidth());
        dislink->setSizePolicy(sizePolicy);
        dislink->setMinimumSize(QSize(75, 23));
        dislink->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(dislink, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 4, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 0, 0, 1, 1);

        TcpClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TcpClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 523, 23));
        TcpClient->setMenuBar(menuBar);
        QWidget::setTabOrder(userLineEdit, passwardLineEdit);
        QWidget::setTabOrder(passwardLineEdit, sendBtn);
        QWidget::setTabOrder(sendBtn, signBtn);
        QWidget::setTabOrder(signBtn, resetpwdButton);
        QWidget::setTabOrder(resetpwdButton, link);
        QWidget::setTabOrder(link, dislink);
        QWidget::setTabOrder(dislink, ServerIp);

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QMainWindow *TcpClient)
    {
        TcpClient->setWindowTitle(QApplication::translate("TcpClient", "tcpclient", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        TcpClient->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        signBtn->setText(QApplication::translate("TcpClient", "\346\263\250\345\206\214", Q_NULLPTR));
        sendBtn->setText(QApplication::translate("TcpClient", "\347\231\273\345\275\225", Q_NULLPTR));
        label_6->setText(QApplication::translate("TcpClient", "EricLiu Private Chat Room", Q_NULLPTR));
        label_2->setText(QApplication::translate("TcpClient", "\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        resetpwdButton->setText(QApplication::translate("TcpClient", "\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237", Q_NULLPTR));
        label_3->setText(QApplication::translate("TcpClient", "\346\234\215\345\212\241\345\231\250IP", Q_NULLPTR));
        ServerIp->setText(QApplication::translate("TcpClient", "172.19.20.147", Q_NULLPTR));
        link->setText(QApplication::translate("TcpClient", "\350\277\236\346\216\245", Q_NULLPTR));
        dislink->setText(QApplication::translate("TcpClient", "\346\226\255\345\274\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
