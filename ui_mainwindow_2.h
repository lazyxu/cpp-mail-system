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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
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
    QTextBrowser *revMail_text;
    QPushButton *writeMail_button;
    QLabel *account_label;
    QLabel *revMailnum_lable;

    void setupUi(QMainWindow *MainWindow_2)
    {
        if (MainWindow_2->objectName().isEmpty())
            MainWindow_2->setObjectName(QStringLiteral("MainWindow_2"));
        MainWindow_2->resize(800, 600);
        MainWindow_2->setMinimumSize(QSize(800, 600));
        MainWindow_2->setMaximumSize(QSize(1024, 768));
        MainWindow_2->setIconSize(QSize(34, 17));
        centralwidget = new QWidget(MainWindow_2);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(1024, 768));
        centralwidget->setMaximumSize(QSize(1024, 768));
        revMail_list = new QListWidget(centralwidget);
        revMail_list->setObjectName(QStringLiteral("revMail_list"));
        revMail_list->setGeometry(QRect(10, 40, 241, 551));
        revMail_button = new QPushButton(centralwidget);
        revMail_button->setObjectName(QStringLiteral("revMail_button"));
        revMail_button->setGeometry(QRect(10, 10, 34, 17));
        revMail_button->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QStringLiteral("../images/revMail.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral("../images/revMail.png"), QSize(), QIcon::Normal, QIcon::On);
        revMail_button->setIcon(icon);
        revMail_button->setIconSize(QSize(34, 17));
        revMail_text = new QTextBrowser(centralwidget);
        revMail_text->setObjectName(QStringLiteral("revMail_text"));
        revMail_text->setGeometry(QRect(260, 40, 531, 551));
        writeMail_button = new QPushButton(centralwidget);
        writeMail_button->setObjectName(QStringLiteral("writeMail_button"));
        writeMail_button->setGeometry(QRect(60, 10, 34, 17));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../images/writeMail.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral("../images/writeMail.png"), QSize(), QIcon::Normal, QIcon::On);
        writeMail_button->setIcon(icon1);
        writeMail_button->setIconSize(QSize(34, 17));
        account_label = new QLabel(centralwidget);
        account_label->setObjectName(QStringLiteral("account_label"));
        account_label->setGeometry(QRect(260, 10, 481, 18));
        revMailnum_lable = new QLabel(centralwidget);
        revMailnum_lable->setObjectName(QStringLiteral("revMailnum_lable"));
        revMailnum_lable->setGeometry(QRect(111, 10, 141, 18));
        revMailnum_lable->setFrameShadow(QFrame::Raised);
        revMailnum_lable->setTextFormat(Qt::PlainText);
        revMailnum_lable->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MainWindow_2->setCentralWidget(centralwidget);

        retranslateUi(MainWindow_2);

        QMetaObject::connectSlotsByName(MainWindow_2);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_2)
    {
        MainWindow_2->setWindowTitle(QApplication::translate("MainWindow_2", "Mail System", 0));
        revMail_button->setText(QString());
        writeMail_button->setText(QString());
        account_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow_2: public Ui_MainWindow_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_2_H
