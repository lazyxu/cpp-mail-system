/********************************************************************************
** Form generated from reading UI file 'mainwindow_2.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_2_H
#define UI_MAINWINDOW_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_2
{
public:
    QWidget *centralwidget;
    QListWidget *revMail_list;
    QPushButton *revMail_button;
    QTextBrowser *textBrowser;
    QPushButton *writeMail_button;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow_2)
    {
        if (MainWindow_2->objectName().isEmpty())
            MainWindow_2->setObjectName(QStringLiteral("MainWindow_2"));
        MainWindow_2->resize(1024, 768);
        MainWindow_2->setMinimumSize(QSize(1024, 768));
        MainWindow_2->setMaximumSize(QSize(1024, 768));
        MainWindow_2->setIconSize(QSize(34, 17));
        centralwidget = new QWidget(MainWindow_2);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(1024, 768));
        centralwidget->setMaximumSize(QSize(1024, 768));
        revMail_list = new QListWidget(centralwidget);
        revMail_list->setObjectName(QStringLiteral("revMail_list"));
        revMail_list->setGeometry(QRect(10, 60, 241, 671));
        revMail_button = new QPushButton(centralwidget);
        revMail_button->setObjectName(QStringLiteral("revMail_button"));
        revMail_button->setGeometry(QRect(10, 30, 34, 17));
        revMail_button->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QStringLiteral("../images/revMail.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral("../images/revMail.png"), QSize(), QIcon::Normal, QIcon::On);
        revMail_button->setIcon(icon);
        revMail_button->setIconSize(QSize(34, 17));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(260, 60, 751, 671));
        writeMail_button = new QPushButton(centralwidget);
        writeMail_button->setObjectName(QStringLiteral("writeMail_button"));
        writeMail_button->setGeometry(QRect(60, 30, 34, 17));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../images/writeMail.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral("../images/writeMail.png"), QSize(), QIcon::Normal, QIcon::On);
        writeMail_button->setIcon(icon1);
        writeMail_button->setIconSize(QSize(34, 17));
        MainWindow_2->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_2);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        MainWindow_2->setMenuBar(menubar);

        retranslateUi(MainWindow_2);

        QMetaObject::connectSlotsByName(MainWindow_2);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_2)
    {
        MainWindow_2->setWindowTitle(QApplication::translate("MainWindow_2", "MainWindow", 0));
        revMail_button->setText(QString());
        writeMail_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow_2: public Ui_MainWindow_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_2_H
