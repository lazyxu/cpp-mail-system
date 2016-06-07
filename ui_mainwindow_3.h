/********************************************************************************
** Form generated from reading UI file 'mainwindow_3.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_3_H
#define UI_MAINWINDOW_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_3
{
public:
    QWidget *centralwidget;
    QLineEdit *fromMail;
    QLineEdit *toMail;
    QLineEdit *title;
    QTextEdit *content;
    QLabel *label;
    QPushButton *sendMail_button;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QMainWindow *MainWindow_3)
    {
        if (MainWindow_3->objectName().isEmpty())
            MainWindow_3->setObjectName(QStringLiteral("MainWindow_3"));
        MainWindow_3->resize(640, 480);
        centralwidget = new QWidget(MainWindow_3);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        fromMail = new QLineEdit(centralwidget);
        fromMail->setObjectName(QStringLiteral("fromMail"));
        fromMail->setGeometry(QRect(60, 30, 571, 21));
        toMail = new QLineEdit(centralwidget);
        toMail->setObjectName(QStringLiteral("toMail"));
        toMail->setGeometry(QRect(60, 60, 571, 21));
        title = new QLineEdit(centralwidget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(60, 90, 571, 21));
        content = new QTextEdit(centralwidget);
        content->setObjectName(QStringLiteral("content"));
        content->setGeometry(QRect(10, 120, 621, 331));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 41, 16));
        sendMail_button = new QPushButton(centralwidget);
        sendMail_button->setObjectName(QStringLiteral("sendMail_button"));
        sendMail_button->setGeometry(QRect(520, 450, 114, 32));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 41, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 41, 16));
        MainWindow_3->setCentralWidget(centralwidget);

        retranslateUi(MainWindow_3);

        QMetaObject::connectSlotsByName(MainWindow_3);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_3)
    {
        MainWindow_3->setWindowTitle(QApplication::translate("MainWindow_3", "\345\206\231\344\277\241", 0));
        label->setText(QApplication::translate("MainWindow_3", "\345\217\221\344\273\266\344\272\272", 0));
        sendMail_button->setText(QApplication::translate("MainWindow_3", "\345\217\221\351\200\201", 0));
        label_2->setText(QApplication::translate("MainWindow_3", "\346\224\266\344\273\266\344\272\272", 0));
        label_3->setText(QApplication::translate("MainWindow_3", "\344\270\273\351\242\230", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_3: public Ui_MainWindow_3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_3_H
