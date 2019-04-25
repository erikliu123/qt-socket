/********************************************************************************
** Form generated from reading UI file 'senders.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDERS_H
#define UI_SENDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_senders
{
public:
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *cStatusLbl_2;

    void setupUi(QWidget *senders)
    {
        if (senders->objectName().isEmpty())
            senders->setObjectName(QStringLiteral("senders"));
        senders->resize(400, 300);
        senders->setWindowOpacity(1);
        progressBar = new QProgressBar(senders);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(120, 100, 201, 41));
        progressBar->setStyleSheet(QLatin1String("QProgressBar\n"
"{\n"
"border: 2px solid blue; \n"
"border-radius: 1px; \n"
"text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"background-color: #00FFff; \n"
"width: 10px; \n"
"margin: 0.5px;\n"
"}\n"
""));
        progressBar->setValue(24);
        label = new QLabel(senders);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 110, 60, 16));
        cStatusLbl_2 = new QLabel(senders);
        cStatusLbl_2->setObjectName(QStringLiteral("cStatusLbl_2"));
        cStatusLbl_2->setGeometry(QRect(60, 150, 251, 51));

        retranslateUi(senders);

        QMetaObject::connectSlotsByName(senders);
    } // setupUi

    void retranslateUi(QWidget *senders)
    {
        senders->setWindowTitle(QApplication::translate("senders", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("senders", "\345\267\262\345\256\214\346\210\220", Q_NULLPTR));
        cStatusLbl_2->setText(QApplication::translate("senders", "\346\226\207\344\273\266\345\217\221\351\200\201\344\270\255...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class senders: public Ui_senders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDERS_H
