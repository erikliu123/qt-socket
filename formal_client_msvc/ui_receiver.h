/********************************************************************************
** Form generated from reading UI file 'receiver.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVER_H
#define UI_RECEIVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_receiver
{
public:
    QProgressBar *progressBar;
    QLabel *cStatusL;
    QLabel *label;

    void setupUi(QWidget *receiver)
    {
        if (receiver->objectName().isEmpty())
            receiver->setObjectName(QStringLiteral("receiver"));
        receiver->resize(400, 300);
        progressBar = new QProgressBar(receiver);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(100, 70, 231, 23));
        progressBar->setValue(0);
        cStatusL = new QLabel(receiver);
        cStatusL->setObjectName(QStringLiteral("cStatusL"));
        cStatusL->setGeometry(QRect(40, 110, 331, 71));
        QFont font;
        font.setPointSize(10);
        cStatusL->setFont(font);
        label = new QLabel(receiver);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 70, 61, 21));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);

        retranslateUi(receiver);

        QMetaObject::connectSlotsByName(receiver);
    } // setupUi

    void retranslateUi(QWidget *receiver)
    {
        receiver->setWindowTitle(QApplication::translate("receiver", "Form", Q_NULLPTR));
        cStatusL->setText(QApplication::translate("receiver", "\346\226\207\344\273\266\346\216\245\346\224\266\344\270\255\342\200\246", Q_NULLPTR));
        label->setText(QApplication::translate("receiver", "\345\267\262\345\256\214\346\210\220", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class receiver: public Ui_receiver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVER_H
