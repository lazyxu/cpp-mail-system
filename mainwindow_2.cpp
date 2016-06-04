#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"
#include <iostream>
#include "pop3.h"
#include "mail.hpp"

void MainWindow_2::init()
{
    std::cout << "init\n";
    this->show();
    revMail();
}

void MainWindow_2::revMail()
{
    std::cout << "revMail...\n";
    ui->revMail_list->clear();
    long n = 0, i;
    bool IsDebug = true;
    mail *mailRev;
    pop3 pop3Test("pop3.163.com", "qqq1051814353@163.com", "qqq1051814353");
    if ( pop3Test.LoginPop3(IsDebug) )
        mailRev = pop3Test.ReceiveMail(IsDebug, n);
    for (i=0; i<n; i++) {
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(mailRev[i].info().c_str())));
    }
}

void MainWindow_2::writeMail()
{
    std::cout << "writeMail...\n";
    emit sWriteMail();
}

MainWindow_2::MainWindow_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
        ui->setupUi(this);
        QFont font;
        font.setPointSize(9); // 设置字号
        ui->revMail_list->setFont(font);
        QObject::connect( ui->revMail_button, SIGNAL(clicked()), this, SLOT(revMail()) );
        QObject::connect( ui->writeMail_button, SIGNAL(clicked()), this, SLOT(writeMail()) );
    }

MainWindow_2::~MainWindow_2()
{
    delete ui;
}
