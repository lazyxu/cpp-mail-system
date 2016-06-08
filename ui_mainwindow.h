/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCheckBox *checkBox;
    QPushButton *login_button;
    QCheckBox *checkBox_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *password;
    QLabel *label_title;
    QLabel *label_login;
    QLineEdit *username;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setMaximumSize(QSize(400, 300));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(110, 230, 87, 20));
        login_button = new QPushButton(centralWidget);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setGeometry(QRect(100, 250, 241, 41));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(240, 230, 87, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 160, 62, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 200, 62, 21));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(110, 200, 221, 21));
        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(0, 0, 400, 150));
        label_title->setPixmap(QPixmap(QString::fromUtf8("../images/title.png")));
        label_login = new QLabel(centralWidget);
        label_login->setObjectName(QStringLiteral("label_login"));
        label_login->setGeometry(QRect(10, 160, 90, 90));
        label_login->setPixmap(QPixmap(QString::fromUtf8("../images/login.png")));
        username = new QLineEdit(centralWidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(110, 160, 221, 21));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "https://github.com/MeteorKL/cpp-mail-system", 0));
        checkBox->setText(QApplication::translate("MainWindow", "\350\256\260\344\275\217\345\257\206\347\240\201", 0));
        login_button->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        label->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\277\230\350\256\260\345\257\206\347\240\201", 0));
        label_title->setText(QString());
        label_login->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
